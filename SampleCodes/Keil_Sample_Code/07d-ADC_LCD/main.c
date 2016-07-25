/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to read 10bit ADC value from channel ADC0.1 and 
                display the Raw and Equivalent voltage on LCD.

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
#include "adc.h"
#include "lcd.h"
#include "delay.h"          


int main() 
{
    int adcValue;
    float volt;
    SystemInit();
    ADC_Init();       /* Initialize the ADC module, Note: Max ADC Input voltage 3.3v */
    
    /*Connect RS->P1_16, RW->P1_17, EN->P1_18 and data bus(D4:D7 - P1_20:P1_23)*/
    LCD_SetUp(P1_16,P1_17,P1_18,P_NC,P_NC,P_NC,P_NC,P1_20,P1_21,P1_22,P1_23);
    LCD_Init(2,16);
    
    while(1)
    {
        adcValue = ADC_GetAdcValue(AD0_1); // Read the ADC value of channel AD0.1, Max ADC voltage 3.3v
        volt = (adcValue*3.3)/1023;       // ADC_REF Voltage=3.3v and ADC resolution 10bit
        LCD_GoToLine(0);
        LCD_Printf("ADC0 Value:%4d\nVolt:%f",adcValue,volt);     // Display Raw adc value and Equivalent temp on LCD
    }		  
}


