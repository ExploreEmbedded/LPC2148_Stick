/***************************************************************************************************
                                   ExploreEmbedded	
 ****************************************************************************************************
 * File:   glcd.h
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the GLCD port configurations, CMD list, function prototypes

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
#ifndef _GLCD_H_
#define _GLCD_H_


#include <stdarg.h>
#include "stdutils.h"
#include "delay.h"
//#include "pinsel.h"
#include "gpio.h"

/***************************************************************************************************
                               Precompile Configuration 
 ***************************************************************************************************/

//#define M_GlcdDataPort		2		// Write GLCD Data Port No
//#define M_GlcdControlPort	0		// Write GLCD Control Port No

//#define GLCD_D0	0				// Pin nos
//#define GLCD_D1	1
//#define GLCD_D2	2
//#define GLCD_D3	3
//
//
//#define GLCD_D4	4
//#define GLCD_D5	5
//#define GLCD_D6	6
//#define GLCD_D7	7	
//
//
//#define GLCD_RS  21
//#define GLCD_RW  22  	  
//#define GLCD_EN  23

//#define GLCD_CS1 24
//#define GLCD_CS2 25


/***************************************************************************************************
                 PreCompile configurations to enable/disable the functions
 ***************************************************************************************************
PreCompile configuration to enable or disable the API's.
 1.Required interfaces can be enabled/disabled by configuring its respective macros to 1/0.
 2. By default all the API's are enabled except for FLOAT display.
 3. Displaying of floating number takes huge controller resources and need to be enabled only 
    if required. This implies for other interfaces as well. 
 ***************************************************************************************************/
#define    Enable_GLCD_ScrollMessage          0
#define    Enable_GLCD_DisplayString          1

#define    Enable_GLCD_DisplayNumber   		  1
#define    Enable_GLCD_DisplayFloatNumber     0
#define    Enable_GLCD_Printf                 1
#define    Enable_GLCD_DisplayLogo            0

#define    ENABLE_GLCD_DrawHoriLine           1
#define    ENABLE_GLCD_DrawVertLine           1
#define    ENABLE_GLCD_DrawLine               1
#define    ENABLE_GLCD_DrawRect               1
#define    ENABLE_GLCD_DrawFillRect           1
#define    ENABLE_GLCD_DrawRoundRect          1
#define    ENABLE_GLCD_GetXYData              1
#define    ENABLE_GLCD_DataRead               1
#define    ENABLE_GLCD_SetDot                 1
#define    ENABLE_GLCD_DisplayHorizontalGraph 1
#define    ENABLE_GLCD_DisplayLogo            1
#define    ENABLE_GLCD_DisplayVerticalGraph   1
#define    ENABLE_GLCD_InvertRect             1
#define    ENABLE_GLCD_DrawCircle             1
#define    ENABLE_GLCD_DrawFillCircle         1
/**************************************************************************************************/




/***************************************************************************************************
                               GLCD PORT Configuration 
 ***************************************************************************************************/

//#define M_GlcdDataPins ((1<<GLCD_D0)|(1<<GLCD_D1)|(1<<GLCD_D2)|(1<<GLCD_D3)|(1<<GLCD_D4)|(1<<GLCD_D5)|(1<<GLCD_D6)|(1<<GLCD_D7)) 

//#define M_GlcdDataBusFunction			LPC_PINCON->PINSEL4		//Databus is connceted to PORT2[0:7]
//#define M_GlcdControlBusFunction		LPC_PINCON->PINSEL1		//Control is connceted to PORT0[21:26]
//
//#define M_GlcdDataBusStatus 			pGPIO_DataPort->FIOPIN
//#define M_GlcdDataBusDirection 			pGPIO_DataPort->FIODIR
//
//#define M_GlcdControlBusStatus			pGPIO_ControlPort->FIOPIN
//#define M_GlcdControlBusDirection 		pGPIO_ControlPort->FIODIR
//	
//#define M_GlcdControlBus_SET       		pGPIO_ControlPort->FIOSET
//#define M_GlcdControlBus_CLR       		pGPIO_ControlPort->FIOCLR


/**************************************************************************************************/


/***************************************************************************************************
                             Commonly used LCD macros/Constants
 ***************************************************************************************************/
#define	BLACK 1
#define WHITE 0

#define BlankSpace ' '

#define C_DisplayDefaultDigits_U8            0xffu // Will display the exact digits in the number
#define C_MaxDigitsToDisplay_U8              10u   // Max decimal/hexadecimal digits to be displayed
#define C_NumOfBinDigitsToDisplay_U8         16u   // Max bits of a binary number to be displayed
#define C_MaxDigitsToDisplayUsingPrintf_U8   C_DisplayDefaultDigits_U8 /* Max dec/hexadecimal digits to be displayed using printf */

#define C_GlcdFirstLine_U8 0x00u
#define C_GlcdLastLine_U8 0x07u
#define C_FirstLineNumberAddress_U8 0xB8
#define C_LastLineNumberAddress_U8  0xBF

#define C_MaxBarGraphs_U8 0x04
#define C_LookUpOffset_U8 0x20

/**************************************************************************************************/


/***************************************************************************************************
                                 Struct/Enums used
 ***************************************************************************************************/

typedef struct
{
    uint8_t PageNum;
    uint8_t LineNum;
    uint8_t CursorPos;
    uint8_t InvertDisplay;
    gpioPins_et RS;
    gpioPins_et RW;
    gpioPins_et EN;
	  gpioPins_et CS1;
    gpioPins_et CS2;
    gpioPins_et D0;
    gpioPins_et D1;
    gpioPins_et D2;
    gpioPins_et D3;
    gpioPins_et D4;
    gpioPins_et D5;
    gpioPins_et D6;
    gpioPins_et D7;
}Glcd_Config_st;

/**************************************************************************************************/



/***************************************************************************************************
                             Function Prototypes
 ***************************************************************************************************/
void GLCD_Init(void);
void GLCD_Clear(void);
void GLCD_SetCursor(uint8_t pageNumber,uint8_t lineNumber,uint8_t CursorPosition);
void GLCD_GetCursor(uint8_t *page_ptr,uint8_t *line_ptr,uint8_t *cursor_ptr);
void GLCD_GoToPage(uint8_t pageNumber);
void GLCD_GoToLine(uint8_t var_lineNumber_u8);
void GLCD_GoToNextLine(void);
void GLCD_EnableDisplayInversion(void);
void GLCD_DisableDisplayInversion(void);
void GLCD_DisplayChar(uint8_t var_lcdData_u8);
void GLCD_DisplayString(char *ptr_stringPointer_u8);
void GLCD_ScrollMessage(uint8_t var_lineNumber_u8, char *ptr_msgPointer_u8);
void GLCD_DisplayFloatNumber(double var_floatNum_f32);
void GLCD_DisplayNumber(NumericSystem_et enm_typeOfNumber, uint32_t var_number_u32, uint8_t var_numOfDigitsToDisplay_u8);
void GLCD_Printf(const char *argList, ...);
void GLCD_DisplayLogo(void);
void GLCD_DisplayVerticalGraph(uint8_t var_barGraphNumber_u8, uint8_t var_percentageValue_u8);
void GLCD_DisplayHorizontalGraph(uint8_t var_barGraphNumber_u8, uint8_t var_percentageValue_u8);
uint8_t GLCD_GetXYData(uint8_t x, uint8_t y);
uint8_t GLCD_DataRead(void);
void GLCD_SetDot(uint8_t , uint8_t , uint8_t );
void GLCD_DrawLine(uint8_t , uint8_t , uint8_t , uint8_t , uint8_t );
void GLCD_DrawRect(uint8_t , uint8_t , uint8_t ,uint8_t , uint8_t );
void GLCD_DrawFillRect(uint8_t , uint8_t , uint8_t ,uint8_t , uint8_t );
void GLCD_DrawRoundRect(uint8_t ,uint8_t ,uint8_t ,uint8_t ,uint8_t ,uint8_t );
void GLCD_InvertRect(uint8_t , uint8_t , uint8_t , uint8_t );
void GLCD_DrawCircle(uint8_t , uint8_t , uint8_t , uint8_t );
void GLCD_DrawFillCircle(uint8_t , uint8_t , uint8_t , uint8_t );
void GLCD_DrawHoriLine(uint8_t var_x_u8, uint8_t var_y_u8, uint8_t var_length_u8,uint8_t var_color_u8);

void GLCD_SetUp(
	      gpioPins_et RS,
        gpioPins_et RW,
        gpioPins_et EN,
	      gpioPins_et CS1,
        gpioPins_et CS2,
        gpioPins_et D0,
        gpioPins_et D1,
        gpioPins_et D2,
        gpioPins_et D3,
        gpioPins_et D4,
        gpioPins_et D5,
        gpioPins_et D6,
        gpioPins_et D7 );

/**************************************************************************************************/


#endif
