/***************************************************************************************************
                                   ExploreEmbedded
 ****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to demonstrate Rainbow colour generation using RGB Leds.
                     Program gets the reqguired colour from user through UART and generates the colour using PWM.

This code has been developed and tested on ExploreEmbedded boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link http://www.exploreembedded.com/wiki for awesome tutorials on 8051,PIC,AVR,ARM,Robotics,RTOS,IOT.
ExploreEmbedded invests substantial time and effort developing open source HW and SW tools, to support consider 
buying the ExploreEmbedded boards.
 
The ExploreEmbedded libraries and examples are licensed under the terms of the new-bsd license(two-clause bsd license).
See also: http://www.opensource.org/licenses/bsd-license.php

EXPLOREEMBEDDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
**************************************************************************************************/

#include "pwm.h"
#include "adc.h"
#include "gpio.h"
#include "stdutils.h"
#include "systemInit.h"
#include "uart.h"

#define RED_LED    P0_1
#define GREEN_LED  P0_7
#define BLUE_LED   P0_2


/* start the main program */
int main() 
{
    char colour;
    SystemInit();   //Clock and PLL configuration 
    UART0_Init(9600);
    PWM_Init(255);     /* Initialize the PWM module and the Cycle time(Ton+Toff) is set to 255(similar to arduino) */
    PWM_Start(RED_LED|GREEN_LED|BLUE_LED); 

    PWM_SetDutyCycle(RED_LED,255);
    PWM_SetDutyCycle(GREEN_LED,0);
    PWM_SetDutyCycle(BLUE_LED,0);   

    while(1)
    {
        colour = UART0_RxChar();

        switch(colour)
        {
        case 'v': /* Violet Color */
        case 'V':
            PWM_SetDutyCycle(RED_LED,148);
            PWM_SetDutyCycle(GREEN_LED,0);
            PWM_SetDutyCycle(BLUE_LED,211);
            break;

        case 'i': /* Indigo Color */
        case 'I':
            PWM_SetDutyCycle(RED_LED,75);
            PWM_SetDutyCycle(GREEN_LED,0);
            PWM_SetDutyCycle(BLUE_LED,130);
            break;


        case 'b': /* Blue Color */
        case 'B':
            PWM_SetDutyCycle(RED_LED,0);
            PWM_SetDutyCycle(GREEN_LED,0);
            PWM_SetDutyCycle(BLUE_LED,255);
                    break;
                

        case 'g': /* Green Color */
        case 'G':
            PWM_SetDutyCycle(RED_LED,0);
            PWM_SetDutyCycle(GREEN_LED,255);
            PWM_SetDutyCycle(BLUE_LED,0);
            break;


        case 'y': /* Yellow Color */
        case 'Y':
            PWM_SetDutyCycle(RED_LED,255);
            PWM_SetDutyCycle(GREEN_LED,255);
            PWM_SetDutyCycle(BLUE_LED,0);
            break;


        case 'o': /* Orange Color */
        case 'O':
            PWM_SetDutyCycle(RED_LED,255);
            PWM_SetDutyCycle(GREEN_LED,127);
            PWM_SetDutyCycle(BLUE_LED,0);
            break;


        case 'r': /* red Color */
        case 'R':
            PWM_SetDutyCycle(RED_LED,255);
            PWM_SetDutyCycle(GREEN_LED,0);
            PWM_SetDutyCycle(BLUE_LED,0);
            break;

        default:  /* Do nothing */
            UART0_Printf("\n\rInvalid Colour ");
            break;

        }                 
    }                             
}
