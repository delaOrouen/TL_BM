/**
 * EE/CSE 474: Lab4 drivers starter code
 */

#include "PLL_Header.h"
#include "Lab4_Inits.h"
#include "lab4.h" // my headerfile
#include "SSD2119_Display.h"
#include <stdio.h>
// STEP 0a: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void LED_Init(void) {
   // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
   // GPIO pins.
   volatile unsigned short delay = 0;
   RCGCGPIO |= 0x1020; // Enable PortF and PortN GPIO
   delay++; // Delay 2 more cycles before access GPIO registers
   delay++; 
   GPIODIR_F |= 0x11; // Set PF0 and PF4 to output
   GPIODEN_F |= 0x11; // Set PF0 and PF4 to digital port
   GPIODIR_N |= 0x3; // Set PN0 and PN1 to output
   GPIODEN_N |= 0x3; // Set PN0 and PN1 to digital port
   
   // the following two statements turn off the onboard LEDs
   GPIODATA_F = 0x0; // clear pins F
   GPIODATA_N = 0x0; // clear pins N
}

void button_Init(void) {
   volatile unsigned short delay = 0;
   RCGCGPIO |= (1<<8); // Enable PortJ
   delay++; // Delay 2 more cycles before access GPIO registers
   delay++;
   GPIOCR_J = 0x3; // Enable write access to GPIOPUR J pins 0 and 1
   GPIOPUR_J = 0x3; // Enable pull up resistor on J pins 0 and 1
   GPIODIR_J = 0x0;
   GPIODEN_J = 0x3; // Set PJ0 and pj1 to digital port
}

void ADCReadPot_Init(void) {
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
   volatile unsigned short delay = 0;
   RCGCADC |= 0x1; // enable ADC0 clock gating
   
  // 2.2: Delay for RCGCADC (Refer to page 1073)
   delay++; // Delay 3 more cycles before access GPIO registers
   delay++; 
   delay++; 
   
  // 2.3: Power up the PLL (if not already)
   PLLFREQ0 |= 0x00800000; // we did this for you
   
  // 2.4: Wait for the PLL to lock
   while (PLLSTAT != 0x1); // we did this for you
   
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
   ALTCLKCFG = 0x0; // read datasheet: ADC--maybe look in timer section
   delay++;        // examine register descriptions
   delay++;  
   ADCCC_0 |= 0x1;
   
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
   RCGCGPIO |= 0x10; // enable clock gating on portE 
   
  // 2.7: Delay for RCGCGPIO
   delay++; // Delay 2 more cycles before access GPIO registers
   delay++;
   
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
   GPIOAFSEL_E |= 0x8; 
   
  // 2.9: Clear the GPIODEN bits for the ADC input pins
   GPIODEN_E &= ~(0x8);
   
  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
   GPIOAMSEL_E |= 0x8;
   
  // 2.11: Disable sample sequencer 3 (SS3)
   ADCACTSS_0 &= ~(0x8);
   
  // 2.12: Select timer as the trigger for SS3
   ADCEMUX_0 |= 0x5000; // 
   
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
   ADCSSEMUX3_0 = 0x0; // select from AIN15-AIN0 
   ADCSSMUX3_0 = 0x0; // select AIN0 as the input channel 
   
  // 2.14: Configure ADCSSCTL3 register
   ADCSSCTL3_0 |= 0x2; // end of sequence
   ADCSSCTL3_0 |= 0x4; // enable sample interrupt
   
  // 2.15: Set the SS3 interrupt mask
   ADCIM_0 |= 0x8; 
   
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
   ADCISC_0 |= (1<<3);   // clear the interrupt to prevent going straight to handler
   delay++; // Delay 2 more cycles before access GPIO registers
   delay++;
   EN0 |= (1 << 17);     // enable the ADC interrupt
   
  // 2.17: Enable ADC0 SS3
   ADCACTSS_0 |= 0x8;
}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet
   RCGCTIMER |= 0x1; // Enable Timer 0
   GPTMCTL_0 &= ~(0x1); // Disable timer A
   GPTMCFG_0 &= 0x0; // select 32-bit timer configuration
   GPTMTAMR_0 |= 0x2; // Configure timer0 A to count down
  // Load 16,000,000 into the GPTMTAILR to achieve a 1 Hz blink rate using the 
  // 16 MHz oscillator.
   GPTMTAILR_0 = PRESET2 * 1000000; // no need to do math -- PLL speed
   // GPTMIMR_0 |= 0x1; // enable interrupt on timer0 A Time-Out interrupt mask 
   // when changing clock speed, 16000 MHz won't work -- PLL adjusts clock speed
   // may need to keep track of the PLL speed -- change timer accordingly
   
   // needs to go before timer enable --standerd practice --
   //   GPTMIMR_0 = 0x1; // enable interrupt on timer 0A 
   GPTMADCEV_0 |= 0x1; // enable GPTM A Time-Out Event ADC Trigger Enable
   // the following line enables ADC timer -- rewrite
   GPTMCTL_0 |= (0x20); // good practive to put befor timer enable
   GPTMICR_0 |= 0x1; // restart the timer
   GPTMCTL_0 |= (0x1); // Enable timer0 A
}

void ADCReadTemp_Init(void) {
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
   volatile unsigned short delay = 0;
   RCGCADC |= 0x1; // enable ADC0 clock gating
   
  // 2.2: Delay for RCGCADC (Refer to page 1073)
   delay++; // Delay 3 more cycles before access GPIO registers
   delay++; 
   delay++; 
   
  // 2.3: Power up the PLL (if not already)
   PLLFREQ0 |= 0x00800000; // we did this for you
   
  // 2.4: Wait for the PLL to lock
   while (PLLSTAT != 0x1); // we did this for you
   
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
   ALTCLKCFG = 0x0; // read datasheet: ADC--maybe look in timer section
   delay++;        // examine register descriptions
   delay++;  
   ADCCC_0 |= 0x1; // use alernate clock source define by ALTCLKCFG
   
  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
//   RCGCGPIO |= 0x10; // enable clock gating on portE 
   
  // 2.7: Delay for RCGCGPIO
//   delay++; // Delay 2 more cycles before access GPIO registers
//   delay++;
   
  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
//   GPIOAFSEL_E |= 0x8; 
   
  // 2.9: Clear the GPIODEN bits for the ADC input pins
//   GPIODEN_E &= ~(0x8);
   
  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
   // no need to change
//   GPIOAMSEL_E |= 0x8;
   
  // 2.11: Disable sample sequencer 3 (SS3)
   ADCACTSS_0 &= ~(0x8);
   
  // 2.12: Select timer as the trigger for SS3
   ADCEMUX_0 |= 0x5000; // 
   
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
   // these should do nothing, no need to remove
//   ADCSSEMUX3_0 = 0x0; // select from AIN15-AIN0 
//   ADCSSMUX3_0 = 0x0; // select AIN0 as the input channel 
   
    // configure sample and hold width for 16 ADC clocks
   // ADCSSTSH_0 |= 0x4;
   
  // 2.14: Configure ADCSSCTL3 register
   ADCSSCTL3_0 |= 0xA; // end of sequence, enable: read from temp sensor
   ADCSSCTL3_0 |= 0x4; // enable sample interrupt
   
  // 2.15: Set the SS3 interrupt mask
   ADCIM_0 |= 0x8; 
   
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
   ADCISC_0 |= (1<<3);   // clear the interrupt to prevent going straight to handler
   EN0 |= (1 << 17);     // enable the ADC interrupt
   
  // 2.17: Enable ADC0 SS3
   ADCACTSS_0 |= 0x8;
}


void UART_Init(void) {
   volatile unsigned short delay = 0; 
   
   // enable clock gating to UART module 0
   RCGCUART |= 0x1;
   delay++; 
   delay++; 
   delay++; 
   
   // enable clock gating to GPIO A
   RCGCGPIO |= 0x1;
   delay++; 
   delay++; 
   delay++;
   
   UARTCTL_0 &= ~(0x1);
   
   GPIODIR_A &= 0x0; // reset GPIO something
   
   // enable UART mode on pins PA0-PA1 
   GPIOAFSEL_A |= 0x3;
   
   // enable digital functions for PA0-PA1
   GPIODEN_A |= 0x3;
   
//   // configure PA0-PA1 to NOT be an open drain
//   GPIOODR_A &= ~(0x3);  
  
//   // enable UART mode on pins PA0-PA1 
//   GPIOAFSEL_A |= 0x3;
   
   // encode 1 for pins PA0-PA1 
   GPIOPCTL_A |= 0x11;
   
   UARTLCRH_0 = 0x0;
   
   // disable UART 0 -- and pretty much everything else
//   UARTCTL_0 &= ~(0x1);
   
   
   // write integer portion of Baud Rate Divisor (BRD)
   // perhaps try 104 and 11 based on 9600 and 16 MHz clock
   float myBRD = (16000000.0 / (16.0 * 9600.0));
   UARTIBRD_0 = (uint32_t)(myBRD); // 0x8; -- 115200// 0x68; --9600 // (int)(myBRD); //104; // write 390  baud rate divisor based on 16 MHz clock // CURRENT CONFIGURATION FOR Baud rate: 115200
   
   // write the fraction portion of BRD
   UARTFBRD_0 = (uint32_t)(((myBRD - ((int)myBRD*1.0)) * 64.0) + 0.5); // 0x2C; -- 115200// 0xB;// (int)(((myBRD - ((int)myBRD*1.0)) * 64) + 0.5); // 11; // write 40
   
   printf("BRD Integer:  %i\n", (int)(myBRD));
   printf("BRD Fraction: %i\n ", (int)(((myBRD - ((int)myBRD*1.0)) * 64.0) + 0.5));
   
   // set word length to 8
//   UARTLCRH_0 = 0x0;
   UARTLCRH_0 |= 0x60; 
   
   // disable FIFO, disable parity
   UARTLCRH_0 &= ~(0x2);
   UARTLCRH_0 &= ~(0x10);
   
   // set UART clock source to ALTCLKCFG 
   UARTCC_0 = 0x5;

   // enable the UART, TX -- TRY SWITCHING THIS ORDER
   UARTCTL_0 |= 0x1; 
   UARTCTL_0 |= 0x100; // enable TX
}

void UART2_Init(void) {
   volatile unsigned short delay = 0; 
   // enable clock gating to UART module 2
   RCGCUART |= 0x4;
   delay++; 
   delay++; 
   delay++; 
   
   // enable clock gating to GPIO A
   RCGCGPIO |= 0x1;
   delay++; 
   delay++; 
   delay++;
   
   // disable UART module 2
   UARTCTL_2 &= ~(0x1);
   
  GPIODIR_A &= 0x0; // reset GPIO direction to input
   
   // enable UART mode on pins PA6-PA7, Rx and Tx 
   GPIOAFSEL_A |= 0xC0;
   
   // enable digital functions for PA6-PA7
   GPIODEN_A |= 0xC0;
   
   // encode 1 for pins PA6-PA7 
   GPIOPCTL_A = 0x11000000;
   
   // disable everythig in UARTLCRH
   UARTLCRH_2 = 0x0;   
   
   // write integer portion of Baud Rate Divisor (BRD)
   // perhaps try 104 and 11 based on 9600 and 16 MHz clock
   float myBRD = (16000000.0 / (16.0 * 9600.0));
   UARTIBRD_2 = (uint32_t)(myBRD);
   
   // write the fraction portion of BRD
   UARTFBRD_2 = (uint32_t)(((myBRD - ((int)myBRD*1.0)) * 64.0) + 0.5);
   
   printf("BRD Integer:  %i\n", (int)(myBRD));
   printf("BRD Fraction: %i\n ", (int)(((myBRD - ((int)myBRD*1.0)) * 64.0) + 0.5));
   
   // set word length to 8
   UARTLCRH_2 |= 0x60; 
   
   // disable FIFO, disable parity
   UARTLCRH_2 &= ~(0x2);
   UARTLCRH_2 &= ~(0x10);
   
   // set UART clock source to ALTCLKCFG 
   UARTCC_2 = 0x5;

   // enable the UART, TX -- TRY SWITCHING THIS ORDER
   UARTCTL_2 |= 0x1; 
   UARTCTL_2 |= 0x100;
}

void printLCD_data(float temp, int frequency) {
  // the following line ensures that these two lines are always printed at the 
  // top of the LCD 
  LCD_SetCursor(0,0);  
  
  // the following lines print the tempurature in C, then in F on one line
  LCD_PrintString("The current temperature is ");
  LCD_PrintFloat(temp);
  LCD_PrintString(" C, ");
  LCD_PrintFloat(temp * 1.8 + 32);
  LCD_PrintString(" F.\n");
  
  // the following lines print the frequency of the board
  LCD_PrintString("The current clock frequency is ");
  LCD_PrintInteger(frequency);
  LCD_PrintString(" MHz.");
}



// WHAT IS THIS FUNCTION DOING?
void interrupt_setup(void) {
   volatile unsigned short delay = 0;
   CFGCTRL = 0x2;
   delay++; // Delay 2 more cycles before access Timer registers
   delay++; 
 
   // GPTMICR_0 |= 0x1; // this signals that the timer has not timed-out
}

void timer_setup(void) {
   RCGCTIMER |= 0x3; // Enable Timer 0 and 1
   GPTMCTL_0 &= ~0x1; // Disable timer A
   GPTMCFG_0 = 0x0; // select 32-bit timer configuration
   GPTMTAMR_0 = 0x2; // Configure timer0 A to count down
   // Load 300,000,000 into the GPTMTAILR to achieve a 0.2 Hz blink rate using the 
   // 16 MHz oscillator.
   GPTMTAILR_0 = 0x11E1A300; 
   GPTMCTL_0 |= 0x1; // Enable timer A
   GPTMRIS_0 |= 0x1; // Reset timer A
   
   GPTMIMR_0 |= 0x1; // enable interrupt on timer0 A Time-Out interrupt mask
   
   GPTMCTL_0 |= 0x1; // Enable timer0 A
   EN0 |= 0x80000; // enable timer1A to be used as an interrupt
   
   GPTMCTL_1 &= ~0x1; // Disable timer A
   GPTMCFG_1 = 0x0; // select 32-bit timer configuration
   GPTMTAMR_1 = 0x2; // Configure timer0 A to count down
   // Load 120,000,000 into the GPTMTAILR to achieve a .5 Hz blink rate using the 
   // 16 MHz oscillator.
   GPTMTAILR_1 = 0x7270E00; 
   GPTMCTL_1 |= 0x1; // Enable timer A
   GPTMRIS_1 |= 0x1; // Reset timer A
}