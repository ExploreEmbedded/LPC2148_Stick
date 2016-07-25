/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to demonstrate the RBG color change depending on ADC values. 
                     By varying the ADC value Different colors can be genrated.

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


#include "systemInit.h"
#include "pwm.h"
#include "adc.h"
#include "gpio.h"
#include "stdutils.h"
#include "delay.h"

#define RED_LED    PWM_1		//P0_1
#define GREEN_LED  PWM_2	    //P0_7
#define BLUE_LED   PWM_3		//P0_2


/* start the main program */
int main() 
{
    int red_value,green_value,blue_value;
    SystemInit();   //Clock and PLL configuration 
    ADC_Init();
    PWM_Init(255);     /* Initialize the PWM module and the Cycle time(Ton+Toff) is set to 255(similar to arduino) */
    PWM_Start(RED_LED|GREEN_LED|BLUE_LED); 

  while(1)
    {
     	/* Read the Adc values from 3pots connected to ADC0.1-ADC0.3(P0_28-	P0_30) */
       red_value   =  ADC_GetAdcValue(AD0_1)/4; // LPC2148 has 10 bit adc and the max value will be 1023 
       green_value =  ADC_GetAdcValue(AD0_2)/4; // Since PWM Cycle(Ton+Toff) is 255, the adc value is divide by 4 to get 0-255  
       blue_value  =  ADC_GetAdcValue(AD0_3)/4;
    
       PWM_SetDutyCycle(RED_LED,red_value);
       PWM_SetDutyCycle(GREEN_LED,green_value);
       PWM_SetDutyCycle(BLUE_LED,blue_value);                  
    }                              
}

