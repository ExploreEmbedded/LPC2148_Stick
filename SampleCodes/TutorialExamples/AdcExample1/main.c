#include<lpc214x.h>
#include "lcd.h"        //ExploreEmbedded LCD library which contains the lcd routines
#include "delay.h"      //ExploreEmbedded delay library which contains the delay routines
#include "stdutils.h"
#include "systemInit.h"
        
/* Bit positions of ADCR and ADGR registers */
#define SBIT_RESULT     6u
#define SBIT_CLCKDIV    8u
#define SBIT_BURST      16u
#define SBIT_START      24u
#define SBIT_PDN        21u
#define SBIT_EDGE       27u 
#define SBIT_DONE       31u



int main()
{
    uint16_t adc_result=0;
    SystemInit();                              //Clock and PLL configuration

    /*Connect RS->P1_16, RW->P1_17, EN->P1_18 and data bus(D4:D7 - P1_20:P1_23)*/
    LCD_SetUp(P1_16,P1_17,P1_18,P_NC,P_NC,P_NC,P_NC,P1_20,P1_21,P1_22,P1_23);

  /* Specify the LCD type(2x16) for initialization*/
    LCD_Init(2,16);    

    AD0CR = ((1<<SBIT_PDN) | (10<<SBIT_CLCKDIV));  //Set the clock and Power ON ADC module

    PINSEL1|= 0x01<<24;      	/* Select the P0_28 AD0.1 for ADC function */

    
    while(1)
    {
        AD0CR  |= 0x02;        /* Select Channel 0 by setting 0th bit of ADCR */
        DELAY_us(10);                  /* allow the channel voltage to stabilize*/
        
        util_BitSet(AD0CR,SBIT_START);            /*Start ADC conversion*/

        while(util_GetBitStatus(AD0GDR,SBIT_DONE)==0);  /* wait till conversion completes */

        adc_result = (AD0GDR >> SBIT_RESULT) & 0x3ff;   /*Read the 10bit adc result*/
        
        LCD_GoToLine(0);                      /* Go to First line of 2x16 LCD */
        LCD_Printf("AD0.1: %4d",adc_result);   /* Display 4-digit adc result */  
    }
}
