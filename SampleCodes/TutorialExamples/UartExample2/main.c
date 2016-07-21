#include "uart.h"
#include "stdutils.h"
#include "systemInit.h"

int main()
{
    SystemInit();

    /* Initialize both the UARTs with different Baud rate */
    UART0_Init(9600);   
    UART1_Init(19200);   

    while(1)
    {
        UART0_Printf("Welcome to LPC2148 UART Programming on channel Zero at 9600 baud\n\r"); 
        UART1_Printf("Welcome to LPC2148 UART Programming on channel One at 19200 baud\n\r"); 
    }
}
