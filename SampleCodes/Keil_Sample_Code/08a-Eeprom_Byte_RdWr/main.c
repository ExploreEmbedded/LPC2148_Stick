/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to write A-Z at memory location 0x00 and read it back.
 *              The data read and written is transmitted on UART.  

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
#include "systemInit.h"
#include "uart.h"
#include "eeprom.h"
#include "gpio.h"

/* start the main program */
int main() 
{
    unsigned char eeprom_address = 0x00, write_char = 'A', read_char;
    SystemInit();
    UART0_Init(9600);

    /* Eeprom IC:AT24C16   SDA:P0_3    SCL:P0_2 */        
    EEPROM_Init(AT24C16,P0_3,P0_2);

    for(write_char='A';write_char<='Z';write_char++)
    {
        UART0_Printf("Eeprom Write: %c    ",write_char); //Print the message on UART
        EEPROM_WriteByte(eeprom_address, write_char); // Write the data at memoryLocation    0x00  

        read_char = EEPROM_ReadByte(eeprom_address);  // Read the data from memoryLocation 0x00
        UART0_Printf("Eeprom Read: %c\n\r",read_char); //Print the message on UART
        eeprom_address++;
    }
    
    while (1);		    
}
