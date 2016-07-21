#include "lcd.h"
#include "systemInit.h"

int main() 
{	   
    SystemInit(); 
		 
    /*Connect RS->P1_16, RW->P1_17, EN->P1_18 and data bus(D4:D7 - P1_20:P1_23)*/
    LCD_SetUp(P1_16,P1_17,P1_18,P_NC,P_NC,P_NC,P_NC,P1_20,P1_21,P1_22,P1_23);
    LCD_Init(2,16);
    
    LCD_DisplayString("Explore Embedded");
    LCD_DisplayString("Lcd 4-bit Mode");

    while(1);
}
