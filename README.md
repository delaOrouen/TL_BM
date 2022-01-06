## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [Controls](#controls)

## General info
This project is a bare-metal implementation of a traffic light using a touch-screen LCD and a developement board. Part of my design choiced include timer setup 
and writing a library to access the registers on the developement board. I completed this project as a part of my lab assignment at the University of Washington. 
	
## Technologies
Project is created with:
* TM4C1294 Connected LaunchPad
* EB-LM4F120-L35 LCD Display
* IAR Embedded Workbench IDE - ARM 8.11.3
	
## Setup
1. To run this project, download this project from GitHub.  
2. Download and install IAR Embedded Workbench IDE - ARM 8.11.3. 
3. Connect the LCD display to the TM4C Connected LaunchPad while aligning PN4 on the LaunchPad with the connecter next to R19 on the LCD Display. 
4. Connect the LaunchPad to your computer with a micro-USB-to-A cable. Insert the micro-USB side into your computer, and the USB-A side into your computer.
5. Build the project in IAR and download to the LaunchPad.

## Controls
To start the traffic light, press and hold the circle over the "Enable" label. This will trigger the FSM to flash a red circle for a second, then the LCD will flash
a red circle. Pressing and holding the circle above the "Pedestrian" label will trigger the FSM to flash a red circle for a second, then a yellow circle for a second
before switching to a red circle for another second. At

