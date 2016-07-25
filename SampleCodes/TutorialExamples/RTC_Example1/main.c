#include <lpc214x.h>    //Device specific header file 
#include "lcd.h"        // Explore Embedded LCD library
#include "systemInit.h"  
#include "stdutils.h"  

/* bit position of CCR register */
#define SBIT_CLKEN     0    /* RTC Clock Enable*/
#define SBIT_CLKSRC    4    /* RTC Clock Source Select Bit */

int main()
{
    uint16_t year;
    uint8_t hour, min, sec, date, month;

    SystemInit();           //Clock and PLL configuration

    /*Connect RS->P1_16, RW->P1_17, EN->P1_18 and data bus(D4:D7 - P1_20:P1_23)*/
    LCD_SetUp(P1_16,P1_17,P1_18,P_NC,P_NC,P_NC,P_NC,P1_20,P1_21,P1_22,P1_23);

    /* Specify the LCD type(2x16) for initialization*/
    LCD_Init(2,16);    

    /* Disable RTC clock, reset clock, Enable RTC calibration */
    CCR = ((1<<SBIT_CLKEN ) | (1<<SBIT_CLKSRC));   /* Select and Enable the clock for RTC */

    /* Set Date and Time only once, comment these lines after setting the time and date */                                           
    // Set Date 14th Nov 2015 
    DOM    = 14;   // Update date value 
    MONTH  = 11;   // Update month value
    YEAR   = 2015; // Update year value
    
    // Set Time 10:40:25 AM 
    HOUR   = 10;   // Update hour value 
    MIN    = 40;   // Update min value
    SEC    = 25;   // Update sec value 
    
    while (1)
    {
        /* Read Time */
        hour = HOUR;
        min  = MIN; 
        sec  = SEC; 

        /* Read Date */
        date  = DOM;   
        month = MONTH;  
        year  = YEAR;   

        /* Display date and time on LCD */
        LCD_GoToLine(0);            /* Go to First line of 2x16 LCD */
        LCD_Printf("Time: %2d:%2d:%2d",hour,min,sec);
        LCD_GoToLine(1);            /* Go to Second line of 2x16 LCD */
        LCD_Printf("Date: %2d/%2d/%4u",date,month,year);   
    }   
}
