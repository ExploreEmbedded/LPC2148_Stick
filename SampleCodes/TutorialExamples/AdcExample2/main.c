#include<lpc214x.h>
#include "lcd.h"    //User defined LCD library which contains the lcd routines
#include "delay.h"  //User defined library which contains the delay routines
#include "adc.h"
#include "stdutils.h"
#include "systemInit.h"
        

int main()
{
   uint16_t pot_value,ldr_value, temp_value;
   
   SystemInit();                              //Clock and PLL configuration

    /*Connect RS->P1_16, RW->P1_17, EN->P1_18 and data bus(D4:D7 - P1_20:P1_23)*/
    LCD_SetUp(P1_16,P1_17,P1_18,P_NC,P_NC,P_NC,P_NC,P1_20,P1_21,P1_22,P1_23);
    LCD_Init(2,16);      /* Specify the LCD type(2x16) for initialization*/
    
    ADC_Init();          /* Initialize the ADC */
    while(1)
    {
        pot_value  = ADC_GetAdcValue(AD0_1); /* Read pot value connect to AD0.1(P0_28) */
        ldr_value  = ADC_GetAdcValue(AD0_2); /* Read LDR value connect to AD0.2(P0_29) */
        temp_value = ADC_GetAdcValue(AD0_3); /* Read Temp value connect to AD0.3(P0_30) */

        LCD_GoToLine(0);
        LCD_Printf("POT:%4d",pot_value);
        LCD_Printf("\nLDR:%4d TMP:%3d",ldr_value,temp_value);       
    }
}
