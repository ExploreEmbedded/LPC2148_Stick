#include <lpc214x.h>   

#define SwitchPinNumber 31
#define LedPinNumber    20

/* start the main program */
int main() 
{
    unsigned int  switchStatus;

    PINSEL2 = 0x000000; //Configure the PORT1 Pins as GPIO;
    
    IODIR1 = ((1<<LedPinNumber) | (0<<SwitchPinNumber)); // LED pin as output and Switch Pin as input 

  while(1)
    {

     /* Turn On all the leds and wait for one second */ 
       switchStatus = (IOPIN1>>SwitchPinNumber) & 0x01 ;  // Read the switch status
       
       if(switchStatus == 1)                 //Turn ON/OFF LEDs depending on switch status
       {  
         IOPIN1 = (1<<LedPinNumber);
       }
       else
       {
         IOPIN1 = (0<<LedPinNumber);
       }      
    }
}
