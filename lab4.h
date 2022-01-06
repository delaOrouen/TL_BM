/*
Rouen de la O
1976923 
10/21/2020
Header file for EE 474 lab 4
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__


// To enable/disable clockgating to the GPIO, UART, ADC
#define RCGCGPIO (*(( volatile uint32_t *) 0x400FE608 ))
#define RCGCUART (*(( volatile uint32_t *) 0x400FE618 ))
#define RCGCADC (*((volatile uint32_t *) 0x400FE638 ))

//To set up and change the data for GPIO Pins F, N, J, N
#define GPIOAMSEL_A (*(( volatile uint32_t *) 0x40058528 ))
#define GPIODIR_A (*(( volatile uint32_t *) 0x40058400 ))
#define GPIODEN_A (*(( volatile uint32_t *) 0x4005851C ))
#define GPIOAFSEL_A (*(( volatile uint32_t *) 0x40058420 ))
#define GPIODATA_A (*(( volatile uint32_t *) 0x400583FC ))
#define GPIOIM_A (*(( volatile uint32_t *) 0x40058410 ))
#define GPIOIS_A (*(( volatile uint32_t *) 0x40058404 ))
#define GPIOIEV_A (*(( volatile uint32_t *) 0x4005840C ))
#define GPIORIS_A (*(( volatile uint32_t *) 0x40058414 ))
#define GPIOICR_A (*(( volatile uint32_t *) 0x4005841C ))
#define GPIOODR_A (*(( volatile uint32_t *) 0x4005850C ))
#define GPIOPCTL_A (*(( volatile uint32_t *) 0x4005852C ))
#define GPIODIR_A (*(( volatile uint32_t *) 0x40058400 ))

#define GPIOAMSEL_B (*(( volatile uint32_t *) 0x40059528 ))
#define GPIODIR_B (*(( volatile uint32_t *) 0x40059400 ))
#define GPIODEN_B (*(( volatile uint32_t *) 0x4005951C ))
#define GPIOAFSEL_B (*(( volatile uint32_t *) 0x40059420 ))
#define GPIODATA_B (*(( volatile uint32_t *) 0x400593FC ))
#define GPIOIM_B (*(( volatile uint32_t *) 0x40059410 ))
#define GPIOIS_B (*(( volatile uint32_t *) 0x40059404 ))
#define GPIOIEV_B (*(( volatile uint32_t *) 0x4005940C ))
#define GPIORIS_B (*(( volatile uint32_t *) 0x40059414 ))
#define GPIOICR_B (*(( volatile uint32_t *) 0x4005941C ))

#define GPIOAMSEL_D (*(( volatile uint32_t *) 0x4005B528 ))
#define GPIODIR_D (*(( volatile uint32_t *) 0x4005B400 ))
#define GPIODEN_D (*(( volatile uint32_t *) 0x4005B51C ))
#define GPIOAFSEL_D (*(( volatile uint32_t *) 0x4005B420 ))
#define GPIODATA_D (*(( volatile uint32_t *) 0x4005B3FC ))
#define GPIOIM_D (*(( volatile uint32_t *) 0x4005B410 ))
#define GPIOIS_D (*(( volatile uint32_t *) 0x4005B404 ))
#define GPIOIEV_D (*(( volatile uint32_t *) 0x4005B40C ))
#define GPIORIS_D (*(( volatile uint32_t *) 0x4005B414 ))
#define GPIOICR_D (*(( volatile uint32_t *) 0x4005B41C ))
#define GPIOODR_D (*(( volatile uint32_t *) 0x4005B50C ))
#define GPIOPCTL_D (*(( volatile uint32_t *) 0x4005B52C ))

#define GPIOAFSEL_E (*(( volatile uint32_t *) 0x4005C420 ))
#define GPIODEN_E (*(( volatile uint32_t *) 0x4005C51C ))
#define GPIOAMSEL_E (*(( volatile uint32_t *) 0x4005C528 ))
#define GPIODATA_E (*(( volatile uint32_t *) 0x4005C3FC ))

#define GPIODIR_F (*(( volatile uint32_t *) 0x4005D400 ))
#define GPIODEN_F (*(( volatile uint32_t *) 0x4005D51C ))
#define GPIODATA_F (*(( volatile uint32_t *) 0x4005D3FC ))

#define GPIOAMSEL_J (*(( volatile uint32_t *) 0x40060528 ))
#define GPIODEN_J (*(( volatile uint32_t *) 0x4006051C ))
#define GPIOPUR_J (*(( volatile uint32_t *) 0x40060510 ))
#define GPIOLOCK_J (*(( volatile uint32_t *) 0x40060520 ))
#define GPIOCR_J (*(( volatile uint32_t *) 0x40060524 ))
#define GPIODIR_J (*(( volatile uint32_t *) 0x40060400 ))
#define GPIODATA_J (*(( volatile uint32_t *) 0x400603FC ))
#define GPIOAFSEL_J (*(( volatile uint32_t *) 0x40060420 ))

// the following are for configuring interrupts on port J
#define GPIOIM_J (*(( volatile uint32_t *) 0x40060410 ))
#define GPIOIS_J (*(( volatile uint32_t *) 0x40060404 ))
#define GPIOIEV_J (*(( volatile uint32_t *) 0x4006040C ))
#define GPIORIS_J (*(( volatile uint32_t *) 0x40060414 ))
#define GPIOICR_J (*(( volatile uint32_t *) 0x4006041C ))

#define GPIOAMSEL_K (*(( volatile uint32_t *) 0x40061528 ))
#define GPIODIR_K (*(( volatile uint32_t *) 0x40061400 ))
#define GPIODEN_K (*(( volatile uint32_t *) 0x4006151C ))
#define GPIOAFSEL_K (*(( volatile uint32_t *) 0x40061420 ))
#define GPIODATA_K (*(( volatile uint32_t *) 0x400613FC ))
#define GPIOIM_K (*(( volatile uint32_t *) 0x40061410 ))
#define GPIOIS_K (*(( volatile uint32_t *) 0x40061404 ))
#define GPIOIEV_K (*(( volatile uint32_t *) 0x4006140C ))
#define GPIORIS_K (*(( volatile uint32_t *) 0x40061414 ))
#define GPIOICR_K (*(( volatile uint32_t *) 0x4006141C ))
#define GPIOODR_K (*(( volatile uint32_t *) 0x4006150C ))
#define GPIOPCTL_K (*(( volatile uint32_t *) 0x4006152C ))

#define GPIOAMSEL_L (*(( volatile uint32_t *) 0x40062528 ))
#define GPIODIR_L (*(( volatile uint32_t *) 0x40062400 ))
#define GPIODEN_L (*(( volatile uint32_t *) 0x4006251C ))
#define GPIOAFSEL_L (*(( volatile uint32_t *) 0x40062420 ))
#define GPIODATA_L (*(( volatile uint32_t *) 0x400623FC ))

#define GPIOAMSEL_M (*(( volatile uint32_t *) 0x40063528 ))
#define GPIODIR_M (*(( volatile uint32_t *) 0x40063400 ))
#define GPIODEN_M (*(( volatile uint32_t *) 0x4006351C ))
#define GPIOAFSEL_M (*(( volatile uint32_t *) 0x40063420 ))
#define GPIODATA_M (*(( volatile uint32_t *) 0x400633FC ))
#define GPIOIM_M (*(( volatile uint32_t *) 0x40063410 ))
#define GPIOIS_M (*(( volatile uint32_t *) 0x40063404 ))
#define GPIOIEV_M (*(( volatile uint32_t *) 0x4006340C ))
#define GPIORIS_M (*(( volatile uint32_t *) 0x40063414 ))
#define GPIOICR_M (*(( volatile uint32_t *) 0x4006341C ))
#define GPIOODR_M (*(( volatile uint32_t *) 0x4006350C ))
#define GPIOPCTL_M (*(( volatile uint32_t *) 0x4006352C ))

#define GPIOAMSEL_N (*(( volatile uint32_t *) 0x40064528 ))
#define GPIODIR_N (*(( volatile uint32_t *) 0x40064400 ))
#define GPIODEN_N (*(( volatile uint32_t *) 0x4006451C )) 
#define GPIOAFSEL_N (*(( volatile uint32_t *) 0x40064420 ))
#define GPIODATA_N (*(( volatile uint32_t *) 0x400643FC ))

#define GPIOAMSEL_P (*(( volatile uint32_t *) 0x40065528 ))
#define GPIODIR_P (*(( volatile uint32_t *) 0x40065400 ))
#define GPIODEN_P (*(( volatile uint32_t *) 0x4006551C ))
#define GPIOAFSEL_P (*(( volatile uint32_t *) 0x40065420 ))
#define GPIODATA_P (*(( volatile uint32_t *) 0x400653FC ))
#define GPIOIM_P (*(( volatile uint32_t *) 0x40065410 ))
#define GPIOIS_P (*(( volatile uint32_t *) 0x40065404 ))
#define GPIOIEV_P (*(( volatile uint32_t *) 0x4006540C ))
#define GPIORIS_P (*(( volatile uint32_t *) 0x40065414 ))
#define GPIOICR_P (*(( volatile uint32_t *) 0x4006541C ))
#define GPIOODR_P (*(( volatile uint32_t *) 0x4006550C ))
#define GPIOPCTL_P (*(( volatile uint32_t *) 0x4006552C ))

#define GPIOAMSEL_Q (*(( volatile uint32_t *) 0x40066528 ))
#define GPIODIR_Q (*(( volatile uint32_t *) 0x40066400 ))
#define GPIODEN_Q (*(( volatile uint32_t *) 0x4006651C ))
#define GPIOAFSEL_Q (*(( volatile uint32_t *) 0x40066420 ))
#define GPIODATA_Q (*(( volatile uint32_t *) 0x400663FC ))
#define GPIOIM_Q (*(( volatile uint32_t *) 0x40066410 ))
#define GPIOIS_Q (*(( volatile uint32_t *) 0x40066404 ))
#define GPIOIEV_Q (*(( volatile uint32_t *) 0x4006640C ))
#define GPIORIS_Q (*(( volatile uint32_t *) 0x40066414 ))
#define GPIOICR_Q (*(( volatile uint32_t *) 0x4006641C ))
#define GPIOODR_Q (*(( volatile uint32_t *) 0x4006650C ))
#define GPIOPCTL_Q (*(( volatile uint32_t *) 0x4006652C ))


//To set up and change the data for the used timer
#define RCGCTIMER (*(( volatile uint32_t *) 0x400FE604 ))
#define GPTMCTL_0 (*(( volatile uint32_t *) 0x4003000C ))
#define GPTMCFG_0 (*(( volatile uint32_t *) 0x40030000 ))
#define GPTMTAMR_0 (*(( volatile uint32_t *) 0x40030004 ))
#define GPTMTAILR_0 (*(( volatile uint32_t *) 0x40030028 ))
#define GPTMRIS_0 (*(( volatile uint32_t *) 0x4003001C ))
#define GPTMICR_0 (*((volatile uint32_t *) 0x40030024 )) 
#define GPTMIMR_0 (*((volatile uint32_t *) 0x40030018 )) 
#define GPTMADCEV_0 (*((volatile uint32_t *) 0x40030070 )) 

#define GPTMCTL_1 (*(( volatile uint32_t *) 0x4003100C ))
#define GPTMCFG_1 (*(( volatile uint32_t *) 0x40031000 ))
#define GPTMTAMR_1 (*(( volatile uint32_t *) 0x40031004 ))
#define GPTMTAILR_1 (*(( volatile uint32_t *) 0x40031028 ))
#define GPTMRIS_1 (*(( volatile uint32_t *) 0x4003101C ))
#define GPTMICR_1    (*((volatile uint32_t *)0x40031024 ))
#define GPTMIMR_1 (*((volatile uint32_t *) 0x40031018 )) 


//To setup up and change the data for interrupt 0-31, 32-63
#define EN0 (*((volatile uint32_t *) 0xE000E100))
#define EN1 (*((volatile uint32_t *) 0xE000E104))


//To enable the manipulation of the NVIC registers for enabling interrupts
#define CFGCTRL (*((volatile uint32_t *) 0xE000ED14 ))


//To set up and change the data for ADC 0 or 1
#define ADCCC_0 (*((volatile uint32_t *) 0x40038FC8 ))
#define ADCACTSS_0 (*((volatile uint32_t *) 0x40038000 ))
#define ADCEMUX_0 (*((volatile uint32_t *) 0x40038014 ))
#define ADCSSMUX3_0 (*((volatile uint32_t *) 0x400380A0 ))
#define ADCSSEMUX3_0 (*((volatile uint32_t *) 0x400380B8 ))
#define ADCSSCTL3_0 (*((volatile uint32_t *) 0x400380A4 ))
#define ADCIM_0 (*((volatile uint32_t *) 0x40038008 ))
#define ADCISC_0 (*((volatile uint32_t *) 0x4003800C ))
#define ADCSSFIFO3_0 (*((volatile uint32_t *) 0x400380A8 )) 
#define ADCSSTSH_0 (*((volatile uint32_t *) 0x400380BC )) 
// the following line is to understand the syntax above
// ( change value of data stored in this address((pointer) to address))


// ALTCLKCFG
#define ALTCLKCFG (*((volatile uint32_t *) 0x400FE138 ))


// To setup and configure the UART module 0
#define UARTCTL_0 (*((volatile uint32_t *) 0x4000C030 ))
#define UARTIBRD_0 (*((volatile uint32_t *) 0x4000C024 ))
#define UARTFBRD_0 (*((volatile uint32_t *) 0x4000C028 ))
#define UARTLCRH_0 (*((volatile uint32_t *) 0x4000C02C ))
#define UARTCC_0 (*((volatile uint32_t *) 0x4000CFC8 ))
#define UARTDR_0 (*((volatile uint32_t *) 0x4000C000 ))
#define UARTFR_0 (*((volatile uint32_t *) 0x4000C018 ))

//To setup and configure UART module 2
#define UARTCTL_2 (*((volatile uint32_t *) 0x4000E030 ))
#define UARTIBRD_2 (*((volatile uint32_t *) 0x4000E024 ))
#define UARTFBRD_2 (*((volatile uint32_t *) 0x4000E028 ))
#define UARTLCRH_2 (*((volatile uint32_t *) 0x4000E02C ))
#define UARTCC_2 (*((volatile uint32_t *) 0x4000EFC8 ))
#define UARTDR_2 (*((volatile uint32_t *) 0x4000E000 ))
#define UARTFR_2 (*((volatile uint32_t *) 0x4000E018 ))

// To setup and configure UART module 3
#define UARTCTL_3 (*((volatile uint32_t *) 0x4000F030 ))
#define UARTIBRD_3 (*((volatile uint32_t *) 0x4000F024 ))
#define UARTFBRD_3 (*((volatile uint32_t *) 0x4000F028 ))
#define UARTLCRH_3 (*((volatile uint32_t *) 0x4000F02C ))
#define UARTCC_3 (*((volatile uint32_t *) 0x4000FFC8 ))
#define UARTDR_3 (*((volatile uint32_t *) 0x4000F000 ))
#define UARTFR_3 (*((volatile uint32_t *) 0x4000F018 ))


#endif //__HEADER1_H__