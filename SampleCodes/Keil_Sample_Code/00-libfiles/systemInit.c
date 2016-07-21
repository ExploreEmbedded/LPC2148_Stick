/***************************************************************************************************
                                   ExploreEmbedded    
****************************************************************************************************
 * File:   systemInit.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library routines for LPC2148 System Init(PLL configuration).

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
***************************************************************************************************/




/***************************************************************************************************
                             Revision History
****************************************************************************************************
15.0: Initial version 
***************************************************************************************************/
#include <lpc214x.h>
#include "stdutils.h"


/***************************************************************************************************
                        void SystemInit(void)
****************************************************************************************************
 * I/P Arguments: none.
 * Return value  : none

 * description  :This function is used to enable the PLL and set the operating freq to 60Mhz
***************************************************************************************************/
#define PLOCK 0x00000400

void SystemInit(void)
{

   PLL0CON = 0x01; // PPLE=1 & PPLC=0, only PLL enabled but not connected 
   PLL0CFG = 0x24; // set the multipler to 5 (i.e actually 4)  12x5 = 60 Mhz (M - 1 = 4)!!!
                   // Set P=2 since we want FCCO in range!!!
                   // So , Assign PSEL =01 in PLL0CFG as per the table.


   PLL0FEED = 0xAA; // Unlock the PLL registers by sending the sequence(0xAA-0x55)
   PLL0FEED = 0x55;


       // check whether PLL has locked on to the  desired freq by reading the lock bit
     // in the PPL0STAT register

   while( !( PLL0STAT & PLOCK ))
     {
         ;
     }

     // now enable(again) and connect
    PLL0CON = 0x03;


   PLL0FEED = 0xAA; // lock the PLL registers after setting the required PLL
   PLL0FEED = 0x55;

   VPBDIV = 0x01; // PCLK is same as CCLK i.e 60Mhz  
}
