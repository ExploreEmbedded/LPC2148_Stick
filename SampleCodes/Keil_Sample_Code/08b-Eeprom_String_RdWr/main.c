/***************************************************************************************************
                                   ExploreEmbedded
 ****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to write a string at memory location 0x00 and read it back.
 *              The string read and written is transmitted on UART.  

This code has been developed and tested on ExploreEmbedded boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link http://www.exploreembedded.com/wiki for awesome tutorials on 8051,PIC,AVR,ARM,Robotics,RTOS,IOT.
ExploreEmbedded invests substantial time and effort developing open source HW and SW tools, to support consider 
buying the ExploreEmbedded boards.
 
The ExploreEmbedded libraries and examples are licensed under the terms of the new-bsd license(two-clause bsd license).
See also: http://www.opensource.org/licenses/bsd-license.php

EXPLOREEMBEDDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
**************************************************************************************************/

#include "uart.h"
#include "systemInit.h"
#include "eeprom.h"

/* start the main program */
int main() 
{
    char write_str[] = "Welcome to ARM programming by Explore Embedded";
    char read_str[50];
	uint16_t eeprom_address = 0x00;

	SystemInit();
    UART0_Init(9600);	 	          
    EEPROM_Init(AT24C16,P0_3,P0_2);		  /* Eeprom IC:AT24C16   SDA:P0_3    SCL:P0_2 */ 

    UART0_Printf("\n\rEeprom Write String: %s", write_str); //Print the message on UART
    EEPROM_WriteString(eeprom_address, write_str); // Write the string at memoryLocation    0x00


    EEPROM_ReadString(eeprom_address, read_str); // Read the string from memoryLocation 0x00
    UART0_Printf("\n\rEeprom Read String: %s", read_str); //Print the message on UART

    while (1);
}
