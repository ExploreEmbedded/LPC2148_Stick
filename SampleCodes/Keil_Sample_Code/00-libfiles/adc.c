/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   adc.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library function for ADC conversion
 
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
#include"adc.h"
#include"delay.h"
#include "stdutils.h"
#include "systemInit.h"
#include "gpio.h"





const adcChannelConfig_st AdcZeroConfig[C_MaxAdcZeroChannels_U8]=
{
        { P_NC,  PINSEL_FUNC_0}, /* AD0[0] is Not available physically, hence marked as P_NC */
        { P0_28, PINSEL_FUNC_1}, /* AD0[1] is on P0_28 second alternative function */
        { P0_29, PINSEL_FUNC_1}, /* AD0[2] is on P0_29 second alternative function */
        { P0_30, PINSEL_FUNC_1}, /* AD0[3] is on P0_30 second alternative function */
        { P0_25, PINSEL_FUNC_1}, /* AD0[4] is on P0_25 Second alternative function */
        { P_NC,  PINSEL_FUNC_0}, /* AD0[5] is Not available physically, hence marked as P_NC */
        { P0_4,  PINSEL_FUNC_3}, /* AD0[6] is on P0_4  Fourth alternative function */
        { P0_5,  PINSEL_FUNC_3}, /* AD0[7] is on P0_5  Fourth alternative function */
};




const adcChannelConfig_st AdcOneConfig[C_MaxAdcOneChannels_U8]=
{
        { P0_6,  PINSEL_FUNC_3}, /* AD1[0] is on P0_6 Fourth alternative function*/
        { P0_8,  PINSEL_FUNC_3}, /* AD1[1] is on P0_8 Fourth alternative function */
        { P0_10, PINSEL_FUNC_3}, /* AD1[2] is on P0_10 Fourth alternative function */
        { P0_12, PINSEL_FUNC_3}, /* AD1[3] is on P0_12 Fourth alternative function */
        { P0_13, PINSEL_FUNC_3}, /* AD1[4] is on P0_13 Fourth alternative function */
        { P0_15, PINSEL_FUNC_3}, /* AD1[5] is on P0_15  Fourth alternative function */
        { P0_21, PINSEL_FUNC_2}, /* AD1[6] is on P0_21  Third alternative function */
        { P0_22, PINSEL_FUNC_1}, /* AD1[7] is on P0_22  Second alternative function */
};


/***************************************************************************************************
                         void ADC_Init()
****************************************************************************************************
 * I/P Arguments: none.
 * Return value : none

 * description :This function initializes the ADC module.
                Refer adc.h for ADC configuration

***************************************************************************************************/
void ADC_Init()
{
     uint32_t v_Pclk_u32;


    v_Pclk_u32 = M_GetClkDivValue();

    AD0CR = ((1<<SBIT_PDN) | v_Pclk_u32);  // no START, no BURST, ADC normal operation, with selected channel
    AD1CR = ((1<<SBIT_PDN) | v_Pclk_u32);  // no START, no BURST, ADC normal operation, with selected channel
}



/***************************************************************************************************
                         uint16_t ADC_GetAdcValue(uint8_t v_adcChannel_u8)
****************************************************************************************************
 * I/P Arguments: uint8_t - channel number(AD0_0 - AD1_7) Refer adc.h file.
 * Return value : uint16_t(10 bit ADC result)

 * description  :This function does the ADC conversion for the Selected Channel
                 and returns the converted 10 bit result
                 The ADC value per bit depends on the resolution of the ADC.
***************************************************************************************************/
uint16_t ADC_GetAdcValue(uint8_t v_adcChannel_u8)
 {
    uint16_t v_adcResult_u16;
    if(v_adcChannel_u8 <= AD0_7)
    {

       /* Select channel is with range, COnfigure the channel for ADC and DO the A/D conversion */
       GPIO_PinFunction(AdcZeroConfig[v_adcChannel_u8].pinNumber,AdcZeroConfig[v_adcChannel_u8].PinFunSel);
       AD0CR  = (AD0CR  & 0xFFFFFF00) | (0x01 << v_adcChannel_u8 );       /* set the channel */

       DELAY_us(10);        /* allow the channel voltage to stabilize*/

       util_BitSet(AD0CR,SBIT_START);           /*Start ADC conversion*/
       while(util_GetBitStatus(AD0GDR,SBIT_DONE)==0);   /* wait till conversion completes */

       v_adcResult_u16 = (AD0GDR >> SBIT_RESULT) & 0x3ff; /*Read the 10bit adc result*/
       util_BitClear(AD0CR,SBIT_START);
    }
    else if((v_adcChannel_u8 >= AD1_0) && (v_adcChannel_u8<= AD1_7))
    {
        v_adcChannel_u8 = v_adcChannel_u8 - AD1_0;

        /* Select channel is with range, COnfigure the channel for ADC and DO the A/D conversion */
        GPIO_PinFunction(AdcOneConfig[v_adcChannel_u8].pinNumber,AdcOneConfig[v_adcChannel_u8].PinFunSel);
        AD1CR  = (AD1CR  & 0xFFFFFF00) | (0x01 << v_adcChannel_u8 );       /* set the channel */

        DELAY_us(10);        /* allow the channel voltage to stabilize*/

        util_BitSet(AD1CR,SBIT_START);           /*Start ADC conversion*/
        while(util_GetBitStatus(AD1GDR,SBIT_DONE)==0);   /* wait till conversion completes */
        
        v_adcResult_u16 = (AD1GDR >> SBIT_RESULT) & 0x3ff; /*Read the 10bit adc result*/
        util_BitClear(AD1CR,SBIT_START);
    }
    else
    {
        /* Channel is out of range, return 0*/
      v_adcResult_u16 = 0;
    }

    return(v_adcResult_u16);                                  /* Return the 10-bit result */
 }

