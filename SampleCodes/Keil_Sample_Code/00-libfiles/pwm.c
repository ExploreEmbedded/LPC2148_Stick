/***************************************************************************************************
                                   ExploreEmbedded    
 ****************************************************************************************************
 * File:   pwm.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library function for PWM generation for lpc1768

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
#include <lpc214x.h>
#include "pwm.h"
#include "gpio.h"
#include "stdutils.h"
#include "uart.h"


static uint32_t pwmInitDoneFlag_u32 = 0;

/***************************************************************************************************
                        void PWM_Init(uint32_t cycleTime)
 ****************************************************************************************************
 * I/P Arguments   : uint32_t- PWM cycle time(Ton+Toff).
 * Return value    : none

 * description :This function initializes the internal PWM1 module of lpc1768.
                By default the pwm  cycle(Ton+Toff) is set 255 to match the arduino style.
 ***************************************************************************************************/
void PWM_Init(uint32_t cycleTime)
{

    PWMTCR = TCR_RESET;    /* Counter Reset */ 
    PWMPR = 0x0;        /* count frequency:Fpclk */
    PWMMCR = 3;    /* interrupt on PWMMR0, reset on PWMMR0, reset TC if PWM matches */                
    PWMMR0 = cycleTime;        /* set PWM cycle(Ton+Toff) */
    PWMLER = LER0_EN; 
    PWMTCR = TCR_CNT_EN | TCR_PWM_EN;    /* counter enable, PWM enable */
}




/***************************************************************************************************
                         void PWM_SetDutyCycle( uint32_t pin, uint32_t dutyCycle )
 ****************************************************************************************************
 * I/P Arguments: uint32_t: Pin number at which PWM needs to be generated.(PWM_1 - PWM_5).
                  uint32_t : required dutyCycle at the pwm pin.
 * Return value    : none

 * description :This function initializes the internal PWM1 module of lpc1768.
                By default the pwm  cycle(Ton+Toff) is set 255 to match the arduino style.
 ***************************************************************************************************/
void PWM_SetDutyCycle( uint32_t pin, uint32_t dutyCycle )
{  
    uint32_t pinSelect=0;

    if(pwmInitDoneFlag_u32 == 0)
    {
        PWM_Init(PWM_CYCLE);   // Set the PWM_CYCLE to 255 if user has not called the PWM_Init function.
        pwmInitDoneFlag_u32 = 1;
    }  

    pin = pin & PWM_CHANNEL_MASK; /* Ensure only supported channel bits are set */


    while(pin)
    {
        pinSelect = ((~pin)+1) & pin; /* Extract the first bit  from left side */
        pin = pin & (~pinSelect);     /* Clear the Bit after extracting, as it is being processed now*/

        switch(pinSelect)
        {
        case PWM_1:
            GPIO_PinFunction(P0_0,PINSEL_FUNC_2);
            PWMMR1 = dutyCycle;
            PWMLER|= LER1_EN; 

            break;

        case PWM_2:
            GPIO_PinFunction(P0_7,PINSEL_FUNC_2);
            PWMMR2 = dutyCycle;
            PWMLER|= LER2_EN;

            break;

        case PWM_3:
            GPIO_PinFunction(P0_1,PINSEL_FUNC_2);
            PWMMR3 = dutyCycle;
            PWMLER|= LER3_EN; 

            break;

        case PWM_4:
            GPIO_PinFunction(P0_8,PINSEL_FUNC_2);
            PWMMR4 = dutyCycle;
            PWMLER|= LER4_EN; 
            break;

        case PWM_5:
            GPIO_PinFunction(P0_21,PINSEL_FUNC_1);
            PWMMR5 = dutyCycle;
            PWMLER|= LER5_EN; 
            break;

        case PWM_6:
            GPIO_PinFunction(P0_9,PINSEL_FUNC_2);
            PWMMR6 = dutyCycle;
            PWMLER|= LER6_EN; 
            break;

        default :
            break;            
        }
    }
}        




/***************************************************************************************************
                         void PWM_Start(uint32_t pin)
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description :This function is used to start the pwm generation..
 ***************************************************************************************************/
void PWM_Start(uint32_t pin)
{
    uint32_t pinSelect=0;   


    if(pwmInitDoneFlag_u32 == 0)
    {
        PWM_Init(PWM_CYCLE);   // Set the PWM_CYCLE to 255 if user has not called the PWM_Init function.
        pwmInitDoneFlag_u32 = 1;
    }  

    pin = pin & PWM_CHANNEL_MASK; /* Ensure only supported channel bits are set */

    while(pin)
    {
        pinSelect = ((~pin)+1) & pin; /* Extract the first bit  from left side */
        pin = pin & (~pinSelect);     /* Clear the Bit after extracting, as it is being processed now*/

        switch(pinSelect)
        {
        case PWM_1:
            PWMPCR |= PWMENA1; 
            break;

        case PWM_2:
            PWMPCR |= PWMENA2;             
            break;

        case PWM_3:
            PWMPCR |= PWMENA3;
            break;

        case PWM_4:
            PWMPCR |= PWMENA4;
            break;

        case PWM_5:
            PWMPCR |= PWMENA5;
            break;

        case PWM_6:
            PWMPCR |= PWMENA6;
            break;

        default :
            break;            
        }
    }   
}




/***************************************************************************************************
                        void PWM_Stop(uint32_t pin)
 ****************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description :This function is used to stop the pwm generation..
 ***************************************************************************************************/
void PWM_Stop(uint32_t pin)
{
    uint32_t pinSelect=0;   

    pin = pin & PWM_CHANNEL_MASK; /* Ensure only supported channel bits are set */

    while(pin)
    {
        pinSelect = ((~pin)+1) & pin; /* Extract the first bit  from left side */
        pin = pin & (~pinSelect);     /* Clear the Bit after extracting, as it is being processed now*/

        switch(pin)
        {
        case PWM_1:
            PWMPCR &=~PWMENA1;
            break;

        case PWM_2:
            PWMPCR &=~PWMENA2;              
            break;

        case PWM_3:
            PWMPCR &=~PWMENA3;
            break;

        case PWM_4:
            PWMPCR &=~PWMENA4;
            break;

        case PWM_5:
            PWMPCR &=~PWMENA5;
            break;

        case PWM_6:
            PWMPCR &=~PWMENA6;
            break;

        default :
            break;            
        }
    }   
}
