#include "lcd.h"
#include "systemInit.h"

int main() 
{	   
    SystemInit(); 
		 
    /*Connect RS->P1_27, RW->P1_28, EN->P1_29 and data bus(D4:D7 - P1_16:P1_23)*/
    LCD_SetUp(P1_27,P1_28,P1_29,P1_16,P1_17,P1_18,P1_19,P1_20,P1_21,P1_22,P1_23);
    LCD_Init(2,16);
    
    LCD_DisplayString("Explore Embedded");
    LCD_DisplayString("Lcd 8-bit Mode");

    while(1);
}
