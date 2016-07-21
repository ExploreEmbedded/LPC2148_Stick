/***************************************************************************************************
                                   ExploreEmbedded    
****************************************************************************************************
 * File:   rtc.c
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Contains the library functions for RTC- date and time read write

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
#include "rtc.h"







/***************************************************************************************************
                         void RTC_Init(void)
 ***************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description :This function is used to Initialize the  RTC.
***************************************************************************************************/
void RTC_Init(void)
{
   
    CCR = ((1<<SBIT_CLKEN ) | (1<<SBIT_CLKSRC));
}











/***************************************************************************************************
                    void RTC_SetDateTime(rtc_t *rtc)
****************************************************************************************************
 * I/P Arguments: rtc_t *: Pointer to structure of type rtc_t. Structure contains hour,min,sec,day,date,month and year 
 * Return value    : none

 * description  :This function is used to set Date(dd,mm,yy) into the  RTC.
                 The new Date is updated into the non volatile memory of RTC .
        Note: The I/P arguments should of hex or decimal 
          like 15,08,2047 for 15th day,8th month and 2047th year.                 
***************************************************************************************************/
void RTC_SetDateTime(rtc_t *rtc)
{

     SEC   =  rtc->sec;       // Update sec value
     MIN   =  rtc->min;       // Update min value
     HOUR    =  rtc->hour;       // Update hour value 
     DOW    =  rtc->weekDay;   // Update day value 
     DOM    =  rtc->date;       // Update date value 
     MONTH =  rtc->month;       // Update month value
     YEAR  =  rtc->year;       // Update year value

}







/***************************************************************************************************
                     void RTC_GetDateTime(rtc_t *rtc)
****************************************************************************************************
 * I/P Arguments: rtc_t *: Pointer to structure of type rtc_t. Structure contains hour,min,sec,day,date,month and year 
 * Return value    : none

 * description  :This function is used to get the Time(hh,mm,ss) And Date from  RTC.

    Note: The time read from  will be of hex or decimal, 
          like 12,39,26 for 12hr,39min and 26sec.    
***************************************************************************************************/
void RTC_GetDateTime(rtc_t *rtc)
{
     rtc->sec     = SEC ;       // Read sec value
     rtc->min     = MIN ;       // Read min value
     rtc->hour    = HOUR;       // Read hour value 
     rtc->weekDay = DOW;      // Read day value 
     rtc->date    = DOM;       // Read date value 
     rtc->month   = MONTH;       // Read month value
     rtc->year    = YEAR;       // Read year value

}







