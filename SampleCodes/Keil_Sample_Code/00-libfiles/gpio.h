/***************************************************************************************************
                                   ExploreEmbedded    
****************************************************************************************************
 * File:   gpio.h
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the the gpio pin number configuration and  
                function prototypes for the gpio routines
 
The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 
 
 
GNU GENERAL PUBLIC LICENSE: 
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
 
 
 /***************************************************************************************************
                             Revision History
****************************************************************************************************                   
15.0: Initial version 
***************************************************************************************************/
 
#ifndef _GPIO_H
#define _GPIO_H

#include"stdutils.h"


typedef enum
{
    P0_0, P0_1, P0_2, P0_3, P0_4, P0_5, P0_6, P0_7, P0_8, P0_9, P0_10,P0_11,P0_12,P0_13,P0_14,P0_15,
    P0_16,P0_17,P0_18,P0_19,P0_20,P0_21,P0_22,P0_23,P0_24,P0_25,P0_26,P0_27,P0_28,P0_29,P0_30,P0_31,

    P1_16,P1_17,P1_18,P1_19,P1_20,P1_21,P1_22,P1_23,P1_24,P1_25,P1_26,P1_27,P1_28,P1_29,P1_30,P1_31,

    P_NC = 0xff
}gpioPins_et; 



/*************************************************************************************************
                           Constants for PIN Function Selection
*************************************************************************************************/
#define PINSEL_FUNC_0 0x00u   
#define PINSEL_FUNC_1 0x01u
#define PINSEL_FUNC_2 0x02u
#define PINSEL_FUNC_3 0x03u
/*************************************************************************************************/




/***************************************************************************************************
                             Function prototypes
***************************************************************************************************/
void GPIO_PinFunction(uint8_t v_pinNumber_u8, uint8_t v_pinFunction_u8);
void GPIO_PinDirection(uint8_t v_pinNumber_u8, uint8_t v_pinDirn_u8);
void GPIO_PinWrite(uint8_t v_pinNumber_u8, uint8_t v_pinValue_u8);
uint8_t GPIO_PinRead(uint8_t v_pinNumber_u8);
/**************************************************************************************************/
#endif
