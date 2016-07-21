#include <lpc214x.h>
#include "stdutils.h"	
#include "systemInit.h"

#define SBIT_WordLenght    0x00u
#define SBIT_DLAB          0x07u
#define SBIT_FIFO          0x00u
#define SBIT_RxFIFO        0x01u
#define SBIT_TxFIFO        0x02u

#define SBIT_RDR           0x00u
#define SBIT_THRE          0x05u

#define TX0_PINSEL            0
#define RX0_PINSEL            2


/* Function to initialize the UART0 at specifief baud rate */
void uart_init(uint32_t baudrate)
{
    uint32_t var_RegValue_u32;

    PINSEL0 |= (1<<RX0_PINSEL) | (1<<TX0_PINSEL);   //Configure P0.0/P0.1 as RX0 and TX0 

    U0FCR = (1<<SBIT_FIFO) | (1<<SBIT_RxFIFO) | (1<<SBIT_TxFIFO); // Enable FIFO and reset Rx/Tx FIFO buffers    
    U0LCR = (0x03<<SBIT_WordLenght) | (1<<SBIT_DLAB);             // 8bit data, 1Stop bit, No parity

    var_RegValue_u32 = ( pclk / (16 * baudrate )); 
    U0DLL =  var_RegValue_u32 & 0xFF;
    U0DLM = (var_RegValue_u32 >> 0x08) & 0xFF;

    util_BitClear(U0LCR,(SBIT_DLAB));  // Clear DLAB after setting DLL,DLM
}


/* Function to transmit a char */
void uart_TxChar(char ch)
{
    while(util_IsBitCleared(U0LSR,SBIT_THRE)); // Wait for Previous transmission
    U0THR=ch;                                  // Load the data to be transmitted
}


/* Function to Receive a char */
char uart_RxChar()
{
 char ch; 
    while(util_IsBitCleared(U0LSR,SBIT_RDR));  // Wait till the data is received
    ch = U0RBR;                                // Read received data    
 return ch;
}


int main()
{
    char ch,a[]="\n\rExploreEmbedded";
    int i;

    SystemInit();
    uart_init(9600);  // Initialize the UART0 for 9600 baud rate

    uart_TxChar('h'); //Transmit "hello" char by char
    uart_TxChar('e');
    uart_TxChar('l');
    uart_TxChar('l');
    uart_TxChar('o');

    for(i=0;a[i];i++)  //transmit a predefined string
        uart_TxChar(a[i]);

    while(1)
    {
        //Finally receive a char and transmit it infinitely
        ch = uart_RxChar(); 
        uart_TxChar(ch);
    }       
}
