#include<lpc214x.h>
#include "lcd.h"    //User defined LCD library which contains the lcd routines
#include "delay.h"  //User defined library which contains the delay routines
        

void main()
{

   /* Setup/Map the controller pins for LCD operation 
               RS   RW   EN    D0    D1    D2   D3     D4   D5    D6    D7*/
    LCD_SetUp(P1_16,P1_17,P1_18,P1_19,P1_20,P1_21,P1_22,P1_23,P1_24,P1_25,P1_26);//P1_20,P1_21,P1_22,P1_23,P1_24,P1_25,P1_26,P1_27);

  /* Specify the LCD type(2x16, 4x16 etc) for initialization*/
    LCD_Init(2,16);

    while(1)
    {
        /*scroll the message on line1 */
        LCD_Clear();
        LCD_ScrollMessage(1,"          Program to demonstrate the ExploreEmbedded Lib Usage");
    
        LCD_Clear();
        LCD_Printf("Hello, World \nGood Morning");
        DELAY_sec(3);
                                  
        LCD_Clear();
        LCD_Printf("DecNum:%4d",1234);
        LCD_Printf("\nHexNum:%4x",0xABCD);
        DELAY_sec(3);
                                  
        LCD_Clear();
        LCD_Printf("16-bit Bin:1234");
        LCD_GoToNextLine();
        LCD_Printf("%16b",0x1234);
        DELAY_sec(3);        
    }
}
