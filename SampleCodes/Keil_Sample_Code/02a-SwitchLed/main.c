/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to read the switch status and display on the Leds. 

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the
library works on any of development boards for respective controllers. However, ExploreEmbedded
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information
related to updates.


GNU GENERAL PUBLIC LICENSE:
    Copyright (C) 2012  ExploreEmbedded

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


Errors and omissions should be reported to codelibraries@exploreembedded.com
**************************************************************************************************/
//#include "gpio.h"

#include <lpc214x.h>   

#define SwitchPinNumber 31
#define LedPinNumber    20

/* start the main program */
int main() 
{
    unsigned int  switchStatus;

    PINSEL2 = 0x000000; //Configure the PORT1 Pins as GPIO;
    
    IODIR1 = ((1<<LedPinNumber) | (0<<SwitchPinNumber)); // LED pin as output and Switch Pin as input 

  while(1)
    {

     /* Turn On all the leds and wait for one second */ 
       switchStatus = (IOPIN1>>SwitchPinNumber) & 0x01 ;  // Read the switch status
       
       if(switchStatus == 1)                 //Turn ON/OFF LEDs depending on switch status
       {  
         IOPIN1 = (1<<LedPinNumber);
       }
       else
       {
         IOPIN1 = (0<<LedPinNumber);
       }      
    }
}

