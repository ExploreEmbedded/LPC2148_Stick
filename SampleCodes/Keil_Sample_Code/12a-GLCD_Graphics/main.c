/***************************************************************************************************
                                   ExploreEmbedded
 ****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to demonstrate the graphics display on 128x64 GLCD.

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


#include "glcd.h"
#include "gpio.h"
#include "systemInit.h"



int main()
{

    int x=20,y=60,color = BLACK;

    /* Setup and initialize the microcontroller */
	  SystemInit();   //Clock and PLL configuration 



    /* Setup/Map the controller pins for GLCD operation
                RS    RW    EN   CS1   CS2   D0    D1    D2    D3    D4    D5     D6     D7*/
    GLCD_SetUp(P1_16, P1_17, P1_18, P1_19, P1_20, P1_21, P1_22, P1_23, P1_24, P1_25, P1_26, P1_27, P1_28);

    /* Initialize the GLCD before use*/

    GLCD_Init();
    GLCD_Printf("GLCD_Graphics Test By \nExploreEmbedded.com");
    DELAY_ms(1000);
    GLCD_Clear();



    GLCD_DrawHoriLine(10,25,50,1);
    GLCD_DrawLine(5,15,5,40,1);
    DELAY_ms(1000);
    GLCD_Clear();


    GLCD_DrawLine(x,0,y,x,color);
    GLCD_DrawLine(y,x,x,y,color);
    GLCD_DrawLine(x,y,0,x,color);
    GLCD_DrawLine(0,x,x,0,color);

    DELAY_ms(1000);
    GLCD_Clear();


    GLCD_DrawCircle(x,x,x,color);
    DELAY_ms(1000);
    GLCD_Clear();

    GLCD_DrawRect((x/2),(x/2),x,x,color);
    DELAY_ms(1000);
    GLCD_Clear();

    GLCD_DrawFillRect((x/2)+2,(x/2)+2,x-4,x-4,color);
    DELAY_ms(1000);
    GLCD_Clear();

    GLCD_InvertRect((x/2)+4,(x/2)+4,x-8,x-8);
    DELAY_ms(1000);
    GLCD_Clear();

    GLCD_InvertRect((x/2)+8,(x/2)+8,x-10,x-10);
    DELAY_ms(1000);
    GLCD_Clear();

    GLCD_DrawFillCircle(x,x,x,(~color));

    GLCD_GoToLine(6);
    GLCD_Printf("Done, Thank You..\n ExploreEmbedded.com");

    while(1);

}

