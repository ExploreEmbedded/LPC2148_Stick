#include<lpc214x.h>

/* Configure the data bus and Control bus as per the hardware connection */
#define LcdDataBusPort       IO1PIN
#define LcdControlBusPort    IO1PIN

#define LcdDataBusDirnReg    IO1DIR
#define LcdCtrlBusDirnReg    IO1DIR

#define LCD_RS     16
#define LCD_RW     17
#define LCD_EN     18

#define LCD_D4     20
#define LCD_D5     21
#define LCD_D6     22
#define LCD_D7     23					 

/* Masks for configuring the DataBus and Control Bus direction */
#define LCD_ctrlBusMask  ((1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN))
#define LCD_dataBusMask  ((1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7))

/* local function to generate some delay */
void delay(int cnt)
{
    int i,j;
    for(i=0;i<cnt;i++)
	for(j=0;j<10;j++);
}


/* Function send the a nibble on the Data bus (LCD_D4 to LCD_D7) */
void sendNibble(char nibble)
{
    LcdDataBusPort&=~(LCD_dataBusMask);                   // Clear previous data
    LcdDataBusPort|= (((nibble >>0x00) & 0x01) << LCD_D4);
    LcdDataBusPort|= (((nibble >>0x01) & 0x01) << LCD_D5);
    LcdDataBusPort|= (((nibble >>0x02) & 0x01) << LCD_D6);
    LcdDataBusPort|= (((nibble >>0x03) & 0x01) << LCD_D7);
}


/* Function to send the command to LCD. 
   As it is 4bit mode, a byte of data is sent in two 4-bit nibbles */
void Lcd_CmdWrite(char cmd)
{
    sendNibble((cmd >> 0x04) & 0x0F);  //Send higher nibble
    LcdControlBusPort &= ~(1<<LCD_RS); // Send LOW pulse on RS pin for selecting Command register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN);

    delay(1000);

    sendNibble(cmd & 0x0F);            //Send Lower nibble
    LcdControlBusPort &= ~(1<<LCD_RS); // Send LOW pulse on RS pin for selecting Command register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN); 

    delay(1000);
}


void Lcd_DataWrite(char dat)
{
    sendNibble((dat >> 0x04) & 0x0F);  //Send higher nibble
    LcdControlBusPort |= (1<<LCD_RS);  // Send HIGH pulse on RS pin for selecting data register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN);

    delay(1000);

    sendNibble(dat & 0x0F);            //Send higher nibble
    LcdControlBusPort |= (1<<LCD_RS);  // Send HIGH pulse on RS pin for selecting data register
    LcdControlBusPort &= ~(1<<LCD_RW); // Send LOW pulse on RW pin for Write operation
    LcdControlBusPort |= (1<<LCD_EN);  // Generate a High-to-low pulse on EN pin
    delay(1000);
    LcdControlBusPort &= ~(1<<LCD_EN); 

    delay(1000);
}



int main()
{
    char i,a[]={"Good morning!"};

    LcdDataBusDirnReg |= LCD_dataBusMask;  // Configure all the LCD pins as output
    LcdCtrlBusDirnReg |= LCD_ctrlBusMask;															 

    Lcd_CmdWrite(0x02);                   // Initialize Lcd in 4-bit mode
    Lcd_CmdWrite(0x28);                   // enable 5x7 mode for chars 
    Lcd_CmdWrite(0x0E);                   // Display OFF, Cursor ON
    Lcd_CmdWrite(0x01);                   // Clear Display
    Lcd_CmdWrite(0x80);                   // Move the cursor to beginning of first line	 

    Lcd_DataWrite('H');
    Lcd_DataWrite('e');
    Lcd_DataWrite('l');
    Lcd_DataWrite('l');
    Lcd_DataWrite('o');
    Lcd_DataWrite(' ');
    Lcd_DataWrite('w');
    Lcd_DataWrite('o');
    Lcd_DataWrite('r');
    Lcd_DataWrite('l');
    Lcd_DataWrite('d');

    Lcd_CmdWrite(0xc0);

    for(i=0;a[i]!=0;i++)
    {
        Lcd_DataWrite(a[i]);
    }

    while(1);
}
