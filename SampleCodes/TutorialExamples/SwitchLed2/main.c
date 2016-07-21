#include "gpio.h"

#define LED1 P1_20
#define LED2 P1_21
#define LED3 P1_22

#define SWITCH1 P0_14
#define SWITCH2 P0_7
#define SWITCH3 P0_15

int main() 
{
    GPIO_PinDirection(LED1,OUTPUT);
    GPIO_PinDirection(LED2,OUTPUT);
    GPIO_PinDirection(LED3,OUTPUT);
    
    GPIO_PinDirection(SWITCH1,INPUT);
    GPIO_PinDirection(SWITCH2,INPUT);
    GPIO_PinDirection(SWITCH3,INPUT);
   
    while(1)
    {
        GPIO_PinWrite(LED1,GPIO_PinRead(SWITCH1));
        GPIO_PinWrite(LED2,GPIO_PinRead(SWITCH2));   
        GPIO_PinWrite(LED3,GPIO_PinRead(SWITCH3));            
    }
}
