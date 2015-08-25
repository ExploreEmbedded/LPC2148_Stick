#include "uart.h"

  #define PLOCK 0x00000400

void System_Init()
{

   PLL0CON = 0x01; // PPLE=1 & PPLC=0, only PLL enabled but not connected 
   PLL0CFG = 0x24; // set the multipler to 5 (i.e actually 4)  12x5 = 60 Mhz (M - 1 = 4)!!!
                   // Set P=2 since we want FCCO in range!!!
                   // So , Assign PSEL =01 in PLL0CFG as per the table.


   PLL0FEED = 0xAA;
   PLL0FEED = 0x55;


       // check whether PLL has locked on to the  desired freq by reading the lock bit
     // in the PPL0STAT register

   while( !( PLL0STAT & PLOCK ));

     // now enable(again) and connect
    PLL0CON = 0x03;


   PLL0FEED = 0xAA;
   PLL0FEED = 0x55;

   VPBDIV = 0x01; // PCLK is same as CCLK i.e 60Mhz  
}


void main()
{

	System_Init();

    UART_Init(0,115200);   // Initilaize All the UARTs at 9600 Baud rate
    UART1_Init(9600);   // Both UART_Init(0,9600) and UART0_Init(9600) are same
                         // Internally UART0_Init() is mapped to UART_Init()
                      	 // You can notice First two(0,1) are called with parameter other two(2,3) with suffix

    /*Directly use the Channel suffixed interface UART0_Printf, where suffix "0" specifies the UART channel*/
    UART0_Printf("Channel Zero at 115200 %4d,  %2x\n\r", 1234, 0xabcd); 
    UART1_Printf("Channel One %4d,   %2x\n\r", 5678, 0xef);



    /*Use the standard interface by passing the channel number as first paramater*/
    UART_Printf(0,"Channel Zero %4d,  %2x\n\r", 1234, 0xabcd);
    UART_Printf(1,"Channel One %4d,   %2x\n\r", 5678, 0xef);

    while(1);
}
