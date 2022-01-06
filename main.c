/*
   Rouen de la O
   12/3/2020
   This file contains the main function for EE 474 lab 4 task 2a. This pgoram 
   runs a an FSM which cycles from green to yellow, then red. When the 
   enable-button is pressed on-screen to disable the FSM, the top three circles 
   disappear. When enable is released and pressed again, those three circles 
   will reappear. When these circles reappear, only the red (right-most) circle 
   will be non-black. 
   This program is implemented using bare-metal programming.
   
*/

#include <stdint.h>
#include <stdio.h>

#include "SSD2119_Display.h"
#include "lab4.h" // my header file
#include "lab4_Inits.h"
#include "PLL_Header.h"
#include "SSD2119_Touch.h"

volatile uint32_t ADC_value;
enum frequency myPRESET = PRESET2;
enum TL_States { TL_SMStart, TL_off, TL_stop, TL_warn, TL_go } TL_State;
enum onButton_States { onButton_SMStart, onButton_Off, onButton_nOn, onButton_On
   , onButton_nOff } onButton_State;
unsigned int pedestrianRecieved; // indicator that the pedestrian's button was pressed
unsigned int enableRecieved;     // indicator that the enable-button was pressed
unsigned int enable;             // global variable to start/stop the traffic light FSM

int main (void) {
   LCD_Init();                // Initialize the LCD screen
   LCD_ColorFill(Color4[3]);  // write every pixel of the LCD to display cyan
   Touch_Init();              // Initialize the touch capabilities of the LCD
   PLL_Init(myPRESET);        // Initialize the PLL
   
   // the following two lines initialize the timer to trigger an interrupt every second
   interrupt_setup(); 
   timer_setup();
   TL_State = TL_SMStart; // initialize the state of the traffic light FSM
   
   // The following two lines draw 2 circles on the LCD
   LCD_DrawFilledCircle(70, 170, 50, 0);
   LCD_DrawFilledCircle(250, 170, 50, 0);
   
   // a label for the enable "button"
   LCD_SetCursor(50,110);  
   LCD_PrintString("enable");
   
   // a label for the pedestrian's "button"
   LCD_SetCursor(220,110);  
   LCD_PrintString("pedestrian");
   
   while (1) {};
         
   return 0;
}

// a function to poll timer 1A second timer
void pollTimer1() {
   GPTMICR_1 |= 0x1; // reset the timer
}

// a function to read whether the enable-circle on the touch-LCD display has been 
// pressed and held for two seconds.
unsigned int isEnableRecieved() {
   enableRecieved = 0;
   int myX = (int)Touch_ReadX();
   int myY = (int)Touch_ReadY();
   // if the enable portion of the screen was pressed
   if ((myX > 750) && (myX <= 1340) && (myY >= 680) && (myY <= 1230)) { 
      pollTimer1();
      while(!(GPTMRIS_1 & 0x1)) { // while the timer has not finished
         myX = (int)Touch_ReadX();
         myY = (int)Touch_ReadY();
         // if the enable portion of the screen was NOT pressed
         if (!((myX > 750) && (myX <= 1340) && (myY >= 680) && (myY <= 1230))) { 
            return 0;
         }
      }
      enableRecieved = 1;
      return 0;
   }
   return 0;
}

// a function to read whether the pedestrian's circle on the touch-LCD display has been 
// pressed and held for two seconds.
unsigned int isPedestrianRecieved() {
   pedestrianRecieved = 0;
   int myX = (int)Touch_ReadX();
   int myY = (int)Touch_ReadY();
   // if the pedestrian portion of the screen was pressed
   if ((myX > 1670) && (myX < 1900) && (myY > 680) && (myY < 1230)) { 
      pollTimer1();
      while(!(GPTMRIS_1 & 0x1)) { // while the timer has not finished
         myX = (int)Touch_ReadX();
         myY = (int)Touch_ReadY();
         // if the pedestrian portion of the screen was NOT pressed
         if (!((myX > 1670) && (myX < 1900) && (myY > 680) && (myY < 1230))) { 
            return 0;
         }
      }
      pedestrianRecieved = 1;
      return 0;
   }
   return 0;
}

// function declaration for an FSM that uses button presses to set and 
// clear GPIO PL5
void onButton()
{
   switch(onButton_State) { // Transitions
      case onButton_SMStart: // Initial Transition
         onButton_State = onButton_Off;
         break;
      case onButton_Off:
         if (enableRecieved) { // test if switch PL1 was pressed
            onButton_State = onButton_nOn;
            break;
         }
         else {
            onButton_State = onButton_Off;  
            break;
         }
      case onButton_nOn:  
         if (! (enableRecieved)) { // test if switch PL1 was not pressed
            onButton_State = onButton_On;
            break;
         }
         else {
            onButton_State = onButton_nOn;  
            break;
         }
      case onButton_On:
         if (enableRecieved) {
            onButton_State = onButton_nOff;
            break;
         }
         else {
            onButton_State = onButton_On;
            break;
         }
      case onButton_nOff:
         if (!(enableRecieved)) {
            onButton_State = onButton_Off;
            break;
         } 
         else {
            onButton_State = onButton_nOff;
            break;
         }
      default:
         onButton_State = onButton_SMStart;
         break;
   } // Transitions
   
      switch(onButton_State) { // State actions
         case onButton_Off:
            enable = 0;
            break;
         case onButton_nOn:
            enable = 1;
            break;
         case onButton_On:
            enable = 1;
            break;
         case onButton_nOff:
            enable = 0;
            break;
         default:
            break;
      } // State actions
}

// function declaration for an FSM that transitions from illuminating a red LED 
// PL2 to green LED PL4 back to red LED PL2. When a circle (button 1) is pressed, yellow 
// a yellow circle is displayed before the red circle. In addition, there is 
// another circle (button) 2 which functions as the enable-button to this FSM.
void trafficLight () {
   switch(TL_State) { // transitions
      case TL_SMStart:
         TL_State = TL_off;
         break;
      case TL_off:
         if (enable) { 
            TL_State = TL_stop;
            break;
         }
         else {
            TL_State = TL_off;
            break;
         }
      case TL_stop:
         if (enable) {
            TL_State = TL_go;
            break;
         }
         else {
            TL_State = TL_off;
            break;
         }
      case TL_warn:
         if (!(enable)) { 
            TL_State = TL_off;
            break;
         }
         else {
            TL_State = TL_stop;
            break;
         }
      case TL_go:
         if (!(enable)) {
            TL_State = TL_off;
            break;
         }
         else if (pedestrianRecieved) { 
            TL_State = TL_warn;
            break;
         }
         else {
            TL_State = TL_stop;
            break;
         }
      default:
         TL_State = TL_SMStart;
         break;
   } // transitions
   
   switch(TL_State) { // state actions
      case TL_off: // clear the screen of the circles
         LCD_DrawFilledCircle( 90, 50, 30, Color4[3]);
         LCD_DrawFilledCircle(160, 50, 30, Color4[3]);
         LCD_DrawFilledCircle(230, 50, 30, Color4[3]);
         break; 
      case TL_stop: // clear all circles excpet for red
         LCD_DrawFilledCircle(90, 50, 30,  0);
         LCD_DrawFilledCircle(160, 50, 30, 0);
         LCD_DrawFilledCircle(230, 50, 30, Color4[12]);
         break;
      case TL_warn: // clear all circles except for yellow
         LCD_DrawFilledCircle(90, 50, 30,  0);
         LCD_DrawFilledCircle(230, 50, 30, 0);
         LCD_DrawFilledCircle(160, 50, 30, Color4[14]);
         break;
      case TL_go: // clear all circles except for green
         LCD_DrawFilledCircle(160, 50, 30, 0);
         LCD_DrawFilledCircle(230, 50, 30, 0);
         LCD_DrawFilledCircle(90, 50, 30,  Color4[10]);
         break;
      default:
         break;
   } // state actions
}





void Timer0A_Handler ( void ) { 
   GPTMICR_0 |= 0x1; // restart the timer
   isEnableRecieved();
   isPedestrianRecieved();
   onButton();
   trafficLight();
}
