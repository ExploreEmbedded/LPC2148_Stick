/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   uart.h   (ARM controllers)
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the baudrate configurations and function prototypes for UART routines

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
#ifndef _ADC_H
#define _ADC_H

#include <lpc214x.h>
#include "stdutils.h"
#include "gpio.h"





/***************************************************************************************************
                             Commonly used ADC macros/Constants
***************************************************************************************************/
#define M_AdcClockFreq      1000000     /* set to 1Mhz */

#define SBIT_BURST   16u
#define SBIT_START   24u
#define SBIT_PDN     21u
#define SBIT_EDGE    27u

#define SBIT_DONE    31u
#define SBIT_RESULT   6u


#define pclk 12000000UL
#define M_GetClkDivValue()  (( pclk  / M_AdcClockFreq - 1u ) << 8u )



/***************************************************************************************************
                            Constants and Structures
***************************************************************************************************/
#define C_MaxAdcZeroChannels_U8  8u
#define C_MaxAdcOneChannels_U8   8u

#define AD0_0       P_NC  /* Physically Not Present */
#define AD0_1       1u
#define AD0_2       2u
#define AD0_3       3u
#define AD0_4       4u
#define AD0_5       P_NC  /* Physically Not Present */
#define AD0_6       6u
#define AD0_7       7u

#define AD1_0       8u
#define AD1_1       9u
#define AD1_2       10u
#define AD1_3       11u
#define AD1_4       12u
#define AD1_5       13u
#define AD1_6       14u
#define AD1_7       15u

typedef struct
{
  gpioPins_et pinNumber;
  uint8_t PinFunSel;
}adcChannelConfig_st;

/**************************************************************************************************/





/***************************************************************************************************
                             Function Prototypes
***************************************************************************************************/
void ADC_Init(void);
uint16_t ADC_GetAdcValue(uint8_t var_adcChannel_u8);

/**************************************************************************************************/


#endif

