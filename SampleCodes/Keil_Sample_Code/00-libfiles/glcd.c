#include "glcd.h"
#include "gpio.h"




Glcd_Config_st glcdConfig;            //Structure containing the selected LCD Configuration


uint8_t shadowBuffer[8][128];
uint8_t ARR_GlcdFont_U8[][7] = {
        {0x00,0x00,0x00,0x00,0x00,0xff,0xff}, /* Space 0x20 */
        {0x00,0x00,0x4f,0x00,0x00,0x00,0xff}, /* ! */
        {0x00,0x07,0x00,0x07,0x00,0x00,0xff}, /* " */
        {0x14,0x7f,0x14,0x7f,0x14,0x00,0xff}, /* # */
        {0x24,0x2a,0x7f,0x2a,0x12,0x00,0xff}, /* 0x */
        {0x23,0x13,0x08,0x64,0x62,0x00,0xff}, /* % */
        {0x36,0x49,0x55,0x22,0x20,0x00,0xff}, /* & */
        {0x00,0x05,0x03,0x00,0x00,0x00,0xff}, /* ' */
        {0x00,0x1c,0x22,0x41,0x00,0x00,0xff}, /* ( */
        {0x00,0x41,0x22,0x1c,0x00,0x00,0xff}, /* ) */
        {0x14,0x08,0x3e,0x08,0x14,0x00,0xff}, /* // */
        {0x08,0x08,0x3e,0x08,0x08,0x00,0xff}, /* + */
        {0x50,0x30,0x00,0x00,0x00,0x00,0xff}, /* , */
        {0x08,0x08,0x08,0x08,0x08,0x00,0xff}, /* - */
        {0x00,0x60,0x60,0x00,0x00,0x00,0xff}, /* . */
        {0x20,0x10,0x08,0x04,0x02,0x00,0xff}, /* / */
        {0x3e,0x51,0x49,0x45,0x3e,0x00,0xff}, /* 0 0x30 */
        {0x40,0x42,0x7f,0x40,0x40,0x00,0xff}, /* 1 */
        {0x42,0x61,0x51,0x49,0x46,0x00,0xff}, /* 2 */
        {0x21,0x41,0x45,0x4b,0x31,0x00,0xff}, /* 3 */
        {0x18,0x14,0x12,0x7f,0x10,0x00,0xff}, /* 4 */
        {0x27,0x45,0x45,0x45,0x39,0x00,0xff}, /* 5 */
        {0x3c,0x4a,0x49,0x49,0x30,0x00,0xff}, /* 6 */
        {0x01,0x71,0x09,0x05,0x03,0x00,0xff}, /* 7 */
        {0x36,0x49,0x49,0x49,0x36,0x00,0xff}, /* 8 */
        {0x06,0x49,0x49,0x29,0x1e,0x00,0xff}, /* 9 */
        {0x00,0x36,0x36,0x00,0x00,0x00,0xff}, /* : */
        {0x00,0x56,0x36,0x00,0x00,0x00,0xff}, /* ; */
        {0x08,0x14,0x22,0x41,0x00,0x00,0xff}, /* < */
        {0x14,0x14,0x14,0x14,0x14,0x00,0xff}, /* = */
        {0x00,0x41,0x22,0x14,0x08,0x00,0xff}, /* > */
        {0x02,0x01,0x51,0x09,0x06,0x00,0xff}, /* ? */
        {0x3e,0x41,0x5d,0x55,0x1e,0x00,0xff}, /* @ 0x40 */
        {0x7e,0x11,0x11,0x11,0x7e,0x00,0xff}, /* A */
        {0x7f,0x49,0x49,0x49,0x36,0x00,0xff}, /* B */
        {0x3e,0x41,0x41,0x41,0x22,0x00,0xff}, /* C */
        {0x7f,0x41,0x41,0x22,0x1c,0x00,0xff}, /* D */
        {0x7f,0x49,0x49,0x49,0x41,0x00,0xff}, /* E */
        {0x7f,0x09,0x09,0x09,0x01,0x00,0xff}, /* F */
        {0x3e,0x41,0x49,0x49,0x7a,0x00,0xff}, /* G */
        {0x7f,0x08,0x08,0x08,0x7f,0x00,0xff}, /* H */
        {0x00,0x41,0x7f,0x41,0x00,0x00,0xff}, /* I */
        {0x20,0x40,0x41,0x3f,0x01,0x00,0xff}, /* J */
        {0x7f,0x08,0x14,0x22,0x41,0x00,0xff}, /* K */
        {0x7f,0x40,0x40,0x40,0x40,0x00,0xff}, /* L */
        {0x7f,0x02,0x0c,0x02,0x7f,0x00,0xff}, /* M */
        {0x7f,0x04,0x08,0x10,0x7f,0x00,0xff}, /* N */
        {0x3e,0x41,0x41,0x41,0x3e,0x00,0xff}, /* O */
        {0x7f,0x09,0x09,0x09,0x06,0x00,0xff}, /* P 0x50 */
        {0x3e,0x41,0x51,0x21,0x5e,0x00,0xff}, /* Q */
        {0x7f,0x09,0x19,0x29,0x46,0x00,0xff}, /* R */
        {0x26,0x49,0x49,0x49,0x32,0x00,0xff}, /* S */
        {0x01,0x01,0x7f,0x01,0x01,0x00,0xff}, /* T */
        {0x3f,0x40,0x40,0x40,0x3f,0x00,0xff}, /* U */
        {0x1f,0x20,0x40,0x20,0x1f,0x00,0xff}, /* V */
        {0x3f,0x40,0x38,0x40,0x3f,0x00,0xff}, /* W */
        {0x63,0x14,0x08,0x14,0x63,0x00,0xff}, /* X */
        {0x07,0x08,0x70,0x08,0x07,0x00,0xff}, /* Y */
        {0x61,0x51,0x49,0x45,0x43,0x00,0xff}, /* Z */
        {0x00,0x7f,0x41,0x41,0x00,0x00,0xff}, /* [ */
        {0x02,0x04,0x08,0x10,0x20,0x00,0xff}, /* \ */
        {0x00,0x41,0x41,0x7f,0x00,0x00,0xff}, /* ] */
        {0x04,0x02,0x01,0x02,0x04,0x00,0xff}, /* ^ */
        {0x40,0x40,0x40,0x40,0x40,0x00,0xff}, /* _ */
        {0x00,0x00,0x03,0x05,0x00,0x00,0xff}, /* ` 0x60 */
        {0x20,0x54,0x54,0x54,0x78,0x00,0xff}, /* a */
        {0x7F,0x44,0x44,0x44,0x38,0x00,0xff}, /* b */
        {0x38,0x44,0x44,0x44,0x44,0x00,0xff}, /* c */
        {0x38,0x44,0x44,0x44,0x7f,0x00,0xff}, /* d */
        {0x38,0x54,0x54,0x54,0x18,0x00,0xff}, /* e */
        {0x04,0x04,0x7e,0x05,0x05,0x00,0xff}, /* f */
        {0x08,0x54,0x54,0x54,0x3c,0x00,0xff}, /* g */
        {0x7f,0x08,0x04,0x04,0x78,0x00,0xff}, /* h */
        {0x00,0x44,0x7d,0x40,0x00,0xff,0xff}, /* i */
        {0x20,0x40,0x44,0x3d,0x00,0xff,0xff}, /* j */
        {0x7f,0x10,0x28,0x44,0x00,0xff,0xff}, /* k */
        {0x41,0x7f,0x40,0x00,0xff,0xff,0xff}, /* l */
        {0x7c,0x04,0x7c,0x04,0x78,0x00,0xff}, /* m */
        {0x7c,0x08,0x04,0x04,0x78,0x00,0xff}, /* n */
        {0x38,0x44,0x44,0x44,0x38,0x00,0xff}, /* o */
        {0x7c,0x14,0x14,0x14,0x08,0x00,0xff}, /* p 0x70 */
        {0x08,0x14,0x14,0x14,0x7c,0x00,0xff}, /* q */
        {0x7c,0x08,0x04,0x04,0x00,0xff,0xff}, /* r */
        {0x48,0x54,0x54,0x54,0x24,0x00,0xff}, /* s */
        {0x04,0x04,0x3f,0x44,0x44,0x00,0xff}, /* t */
        {0x3c,0x40,0x40,0x20,0x7c,0x00,0xff}, /* u */
        {0x1c,0x20,0x40,0x20,0x1c,0x00,0xff}, /* v */
        {0x3c,0x40,0x30,0x40,0x3c,0x00,0xff}, /* w */
        {0x44,0x28,0x10,0x28,0x44,0x00,0xff}, /* x */
        {0x0c,0x50,0x50,0x50,0x3c,0x00,0xff}, /* y */
        {0x44,0x64,0x54,0x4c,0x44,0x00,0xff}, /* z */
        {0x08,0x36,0x41,0x41,0x00,0x00,0xff}, /* { */
        {0x00,0x00,0x77,0x00,0x00,0x00,0xff}, /* | */
        {0x00,0x41,0x41,0x36,0x08,0x00,0xff}, /* } */
        {0x08,0x08,0x2a,0x1c,0x08,0x00,0xff}, /* <- */
        {0x08,0x1c,0x2a,0x08,0x08,0x00,0xff}, /* -> */
        {0xff,0xff,0xff,0xff,0xff,0x00,0xff}, /*  0x80 */
};


static void glcd_SelectPage0(void);
static void glcd_SelectPage1(void);
void glcd_CmdWrite( uint8_t var_cmd_u8);
void glcd_DataWrite( uint8_t var_data_u8);
static void glcd_SendData(uint8_t dataByte);
void glcd_BusyCheck(void);




/**************************************************************************************************
void GLCD_SetUp( pin numbers of lcd)
 ***************************************************************************************************
 * Function name:  LCD_SetUp()
 * I/P Arguments: gpioPins_et RS: Pin where RS is connected 
                  gpioPins_et RW: Pin where RW is connected (P_NC if not connected) 
                  gpioPins_et EN: Pin where EN is connected

                  gpioPins_et D0: Pin where D0 is connected   
                  gpioPins_et D1: Pin where D1 is connected   
                  gpioPins_et D2: Pin where D2 is connected   
                  gpioPins_et D3: Pin where D3 is connected  
                  gpioPins_et D4: Pin where D4 is connected 
                  gpioPins_et D5: Pin where D5 is connected 
                  gpioPins_et D6: Pin where D6 is connected 
                  gpioPins_et D7: Pin where D7 is connected 
 * Return value	: none

 * description  :This function is used to configure the controller pins for LCD operation.
                 Pass the pin numbers where the RS,RW,EN, D0-D7 are connected as parameters.
				 If RW is not used then pass P_NC as parameter for for RS.
 **************************************************************************************************/
void GLCD_SetUp(
	      gpioPins_et RS,
        gpioPins_et RW,
        gpioPins_et EN,
	      gpioPins_et CS1,
        gpioPins_et CS2,
        gpioPins_et D0,
        gpioPins_et D1,
        gpioPins_et D2,
        gpioPins_et D3,
        gpioPins_et D4,
        gpioPins_et D5,
        gpioPins_et D6,
        gpioPins_et D7 )
{
    /* Copy the PIN numbers at whihc the LCD is connected */
    glcdConfig.RS = RS;
    glcdConfig.RW = RW;
    glcdConfig.EN = EN;
	  glcdConfig.CS1 = CS1;
    glcdConfig.CS2 = CS2;

    glcdConfig.D0 = D0;
    glcdConfig.D1 = D1;
    glcdConfig.D2 = D2;
    glcdConfig.D3 = D3;
    glcdConfig.D4 = D4;
    glcdConfig.D5 = D5;
    glcdConfig.D6 = D6;
    glcdConfig.D7 = D7;

    /* Configure CS1,CS2.RS,RW,EN, D0-D7 as Output */
    GPIO_PinDirection(CS1,OUTPUT);
    GPIO_PinDirection(CS2,OUTPUT);
    GPIO_PinDirection(RS,OUTPUT);
    GPIO_PinDirection(RW,OUTPUT);
    GPIO_PinDirection(EN,OUTPUT);

    GPIO_PinDirection(D0,OUTPUT);
    GPIO_PinDirection(D1,OUTPUT);
    GPIO_PinDirection(D2,OUTPUT);
    GPIO_PinDirection(D3,OUTPUT);
    GPIO_PinDirection(D4,OUTPUT);
    GPIO_PinDirection(D5,OUTPUT);
    GPIO_PinDirection(D6,OUTPUT);
    GPIO_PinDirection(D7,OUTPUT);  

}


/**************************************************************************************************
								void GLCD_Init()
 ***************************************************************************************************
 * I/P Arguments:  none
 * Return value	: none

 * description  :This function is used to initialize the graphic lcd.
 *It initializes the LCD for selected mode 8-bit
 **************************************************************************************************/


void GLCD_Init()
{
    /* Select the Page0/Page1 and Enable the GLCD */
    glcdConfig.LineNum = 0xB8;
    glcdConfig.PageNum = 0;
    glcdConfig.CursorPos = 0x40;
    glcd_SelectPage0();
    glcd_CmdWrite(0x3f);
    glcd_SelectPage1();
    glcd_CmdWrite(0x3f);
    DELAY_ms(10);

    /* Select the Page0/Page1 and Enable the GLCD */
    glcd_SelectPage0();
    glcd_CmdWrite(0xc0);
    glcd_SelectPage1();
    glcd_CmdWrite(0xc0);
    GLCD_GoToPage(0);

    /* Clear the complete LCD and move the cursor to beginning of page0*/
    GLCD_Clear();
}



/**************************************************************************************************
								void GLCD_SelectPage0()
 ***************************************************************************************************
 * I/P Arguments:  none
 * Return value	: none

 * description  :This function is used to enable page0 on GLCD
 **************************************************************************************************/

static void glcd_SelectPage0() 
{


    GPIO_PinWrite(glcdConfig.CS1,1);
    GPIO_PinWrite(glcdConfig.CS2,0);
    glcdConfig.PageNum=0;
}



/**************************************************************************************************
								void glcd_SelectPage1()
 ***************************************************************************************************
 * I/P Arguments:  none
 * Return value	: none

 * description  :This function is used to enable page1 on GLCD
 **************************************************************************************************/

static void glcd_SelectPage1() 
{

    GPIO_PinWrite(glcdConfig.CS1,0);
    GPIO_PinWrite(glcdConfig.CS2,1);

    glcdConfig.PageNum=1;

}



/**************************************************************************************************
								void GLCD_SelectBothPage()
 ***************************************************************************************************
 * I/P Arguments:  none
 * Return value	: none

 * description  :This function is used to enable both pages on GLCD
 **************************************************************************************************/




static void glcd_SendData(uint8_t dataByte)
{

    GPIO_PinWrite(glcdConfig.D0,((dataByte) & 0x01));
    GPIO_PinWrite(glcdConfig.D1,((dataByte >> 1) & 0x01));
    GPIO_PinWrite(glcdConfig.D2,((dataByte >> 2) & 0x01));
    GPIO_PinWrite(glcdConfig.D3,((dataByte >> 3) & 0x01));
    GPIO_PinWrite(glcdConfig.D4,((dataByte >> 4) & 0x01));
    GPIO_PinWrite(glcdConfig.D5,((dataByte >> 5) & 0x01));
    GPIO_PinWrite(glcdConfig.D6,((dataByte >> 6) & 0x01));
    GPIO_PinWrite(glcdConfig.D7,((dataByte >> 7) & 0x01));
}

/***************************************************************************************************
                       void glcd_CmdWrite( uint8_t var_lcdCmd_u8)
 ***************************************************************************************************
 * I/P Arguments: 8-bit command supported by graphic LCD.
 * Return value	: none

 * description :This function sends a command to graphic LCD.
                Some of the commonly used commands are defined in glcdConfig.h.
                For more commands refer the data sheet and send the supported command.				
				The behaviour is undefined if unsupported commands are sent.    
 ***************************************************************************************************/
void glcd_CmdWrite( uint8_t var_glcdCmd_u8)
{
    glcd_BusyCheck();
    glcd_SendData((var_glcdCmd_u8));

    GPIO_PinWrite(glcdConfig.RS,0);
    GPIO_PinWrite(glcdConfig.RW,0);
    GPIO_PinWrite(glcdConfig.EN,1);
    DELAY_us(1);
    GPIO_PinWrite(glcdConfig.EN,0);
    DELAY_us(1);
}


/*************************************************************************************************
                       static void glcd_DataWrite( uint8_t dat)
 *************************************************************************************************
 * I/P Arguments: uint8_t: 8-bit value to be sent to LCD.
 * Return value    : none

 * description : This functions is used to send a byte of v_dataRead_u8 to LCD.                 .    
 *************************************************************************************************/
void glcd_DataWrite( uint8_t var_data_u8)
{
    uint8_t temp;

    glcd_BusyCheck();
    temp = var_data_u8; //^ glcdConfig.InvertDisplay;
    glcd_SendData(temp);

    GPIO_PinWrite(glcdConfig.RS,1);
    GPIO_PinWrite(glcdConfig.RW,0);
    GPIO_PinWrite(glcdConfig.EN,1);
    DELAY_us(1);
    GPIO_PinWrite(glcdConfig.EN,0);
    DELAY_us(1);

    shadowBuffer[glcdConfig.LineNum-C_FirstLineNumberAddress_U8][(glcdConfig.PageNum*64)+glcdConfig.CursorPos] = var_data_u8;
    glcdConfig.CursorPos++;
    if((glcdConfig.PageNum == 0x01) && (glcdConfig.CursorPos==0x80))
        GLCD_GoToNextLine();
}







/*************************************************************************************************
                       static void glcd_BusyCheck()
 *************************************************************************************************
 * I/P Arguments: none.
 * Return value    : none

 * description : This functions is used check whether LCD is busy.
                 It waits till the LCD is busy by polling the LCD busy flag.
                 After completing the previous operation, LCDs clears its internal busy flag.
 *************************************************************************************************/
void glcd_BusyCheck()
{

    /*
      uint8_t busyflag;



    	GPIO_PinDirection(glcdConfig.D7,INPUT); // Configure busy pin as input
    GPIO_PinWrite(glcdConfig.RS,0);           // Select the Command Register by pulling RS LOW
	GPIO_PinWrite(glcdConfig.RW,1);           // Select the Read Operation for busy flag by setting RW
	do
    {
        GPIO_PinWrite(glcdConfig.EN,0);	// Send a Low-to-High Pulse at Enable Pin
        DELAY_us(10);    
        GPIO_PinWrite(glcdConfig.EN,1);
        DELAY_us(10);
		busyflag = GPIO_PinRead(glcdConfig.D7);
    }while(busyflag);

	GPIO_PinDirection(glcdConfig.D7,OUTPUT); // Configure busy pin as input
     */
    /* Busy flag cannot be read as GLCD_RW is not available hence Extra delay of 1ms is added
      to ensure the LCD completes previous operation and ready to receive new commands/v_dataRead_u8 */
    DELAY_us(10);
}
/***************************************************************************************************
                         void GLCD_Clear()
 ***************************************************************************************************
 * I/P Arguments: none.
 * Return value	: none

 * description  :This function clears the graphic LCD and 
 				moves the cursor to beginning of first line	on Page0
 ***************************************************************************************************/

void GLCD_Clear()
{
    uint8_t line,cursor;

    for(line=0;line<8;line++)  /* loop through all the 8lines to clear the display */
    {
        /* Go to beginning of the specified line on page0 */
        GLCD_GoToLine(line);
        for(cursor=0;cursor<128;cursor++) /* Clear all the 128 pixels of selected line */
        {
            if(cursor==64)  /* Has the cursor reached end of page0 */
            {
                GLCD_GoToPage(1); /*  then set it to beginning of page1 */
            }

            glcd_DataWrite(0x00); /* Clear each pixel by displaying blank */
        }
    }

    GLCD_GoToLine(0);
}


void GLCD_EnableDisplayInversion()
{
    glcdConfig.InvertDisplay = 0xff;
}



void GLCD_DisableDisplayInversion()
{
    glcdConfig.InvertDisplay = 0x00;
}






/***************************************************************************************************
      void GLCD_SetCursor(uint8_t pageNumber,uint8_t lineNumber,uint8_t CursorPosition)
 ***************************************************************************************************
 * I/P Arguments: 
                 pageNumber -> 0/1  (page0/page1)
                 lineNumber -> 0-7 (line0 - line7)
                 CursorPosition -> 0-63
 * Return value    : none

 * description  :This function moves the Cursor to specified position

                   Note:If the Input(Line/Char number) are out of range 
                        then no action will be taken
 ***************************************************************************************************/
/* TODO: change the var names, Add logic for page handling */
void GLCD_SetCursor(uint8_t pageNumber,uint8_t lineNumber,uint8_t CursorPosition)
{
    if(((pageNumber == 0x00)   || (pageNumber == 0x01)) && (lineNumber <= C_GlcdLastLine_U8) && (CursorPosition < 64) )
    {
        if(pageNumber==0x00)  /* Check for page number and set accordingly */
        {
            glcd_SelectPage0();
        }
        else
        {
            glcd_SelectPage1();
        }
    }

    glcdConfig.PageNum = pageNumber; /* Keep the track of page selected */
    glcdConfig.LineNum=lineNumber | C_FirstLineNumberAddress_U8; /* Select the specified line number */
    glcdConfig.CursorPos=CursorPosition |0x40; /* Select the specified cursor position */

    glcd_CmdWrite(glcdConfig.CursorPos); /* Command the LCD to move to specified page,line,cursor*/
    glcd_CmdWrite(glcdConfig.LineNum);
}


void GLCD_GetCursor(uint8_t *page_ptr,uint8_t *line_ptr,uint8_t *cursor_ptr)
{

    *page_ptr=glcdConfig.PageNum;
    *line_ptr=glcdConfig.LineNum - C_FirstLineNumberAddress_U8;
    *cursor_ptr=glcdConfig.CursorPos;
}



/***************************************************************************************************
                      void GLCD_GoToPage(uint8_t pageNumber)
 ***************************************************************************************************
 * I/P Arguments: uint8_t: Line number.
 * Return value    : none

 * description  :This function moves the Cursor to beginning of the specified line.
        If the requested line number is out of range, it will not move the cursor.

     Note: The line numbers run from 1 to Maxlines,
 ***************************************************************************************************/
/* TODO: change the desp and variable name */
void GLCD_GoToPage(uint8_t pageNumber)
{

    if((pageNumber==0) || (pageNumber ==1))
    { /* for 128/64 GLCD only page 0&1 are supported.
        Select the specified page and move the cursor accordingly */
        if(pageNumber == 0)
        {

            glcd_SelectPage0();
        }
        else
        {
            glcd_SelectPage1();
        }
        glcdConfig.PageNum=pageNumber;
        glcdConfig.CursorPos=0x40;
        glcd_CmdWrite(glcdConfig.LineNum);
        glcd_CmdWrite(glcdConfig.CursorPos);
    }
}







/***************************************************************************************************
                         void GLCD_GoToLine(uint8_t var_lineNumber_u8)
 ***************************************************************************************************
 * I/P Arguments: uint8_t: Line number.
 * Return value    : none

 * description  :This function moves the Cursor to beginning of the specified line.
        If the requested line number is out of range, it will not move the cursor.

     Note: The line numbers run from 0 to Maxlines-1, For 128x64 the line numbers will be 0-7
 ***************************************************************************************************/
/* Todo: All constants for the magic numbers */
void  GLCD_GoToLine(uint8_t var_lineNumber_u8)
{
    if(var_lineNumber_u8<8)
    {   /* If the line number is within range
	     then move it to specified line on page0 and keep track*/
        glcdConfig.LineNum = var_lineNumber_u8+C_FirstLineNumberAddress_U8;
        GLCD_GoToPage(0);
    }
}





/***************************************************************************************************
                         void  GLCD_GoToNextLine()
 ***************************************************************************************************
 * I/P Arguments: none
 * Return value    : none

 * description  :This function moves the Cursor to beginning of the next line.
        If the cursor is on last line and NextLine command is issued then 
        it will move the cursor to first line.
 ***************************************************************************************************/
void  GLCD_GoToNextLine()
{
    /*Increment the current line number.
      In case it exceeds the limit, rool it back to first line */
    glcdConfig.LineNum++;
    if(glcdConfig.LineNum > C_LastLineNumberAddress_U8)
        glcdConfig.LineNum = C_FirstLineNumberAddress_U8;
    GLCD_GoToPage(0); /* Finally move it to next line on page0 */
}






/***************************************************************************************************
                       void GLCD_DisplayChar( char var_lcdData_u8)
 ***************************************************************************************************
 * I/P Arguments: ASCII value of the char to be displayed.
 * Return value    : none

 * description  : This function sends a character to be displayed on LCD.
                  Any valid ascii value can be passed to display respective character

 ***************************************************************************************************/
/* Add the comments for decoding the character, Even offset handling*/
void GLCD_DisplayChar(uint8_t var_lcdData_u8)
{
    uint8_t dat,i=0;

    // ptr= &ARR_GlcdFont_U8[var_lcdData_u8][0]; /* Get the address of the Character pattern from LookUp */
    if(((glcdConfig.PageNum == 0x01) && (glcdConfig.CursorPos>=0x7c)) || (var_lcdData_u8=='\n'))
    {
        /* If the cursor has reached to end of line on page1
        OR NewLine command is issued Then Move the cursor to next line */
        GLCD_GoToNextLine();
    }

    if(var_lcdData_u8!='\n')   /* TODO */
    {

        while(1)
        {
            if((glcdConfig.PageNum == 0x00) && (glcdConfig.CursorPos==0x80))
            {
                /* If the cursor has reached to end of line on page0
                     Then Move the cursor to Page1 */
                GLCD_GoToPage(1);
            }

            dat =ARR_GlcdFont_U8[var_lcdData_u8-0x20][i++];
            if(dat==0xff) /* Exit the loop if End of char is encountered */
                break;

            glcd_DataWrite(dat); /* Display the v_dataRead_u8 and keep track of cursor */

        }
    }
}






/***************************************************************************************************
                       void GLCD_DisplayString(char *ptr_stringPointer_u8)
 ***************************************************************************************************
 * I/P Arguments: String(Address of the string) to be displayed.
 * Return value    : none

 * description  :
               This function is used to display the ASCII string on the lcd.
                 1.The ptr_stringPointer_u8 points to the first char of the string
                    and traverses till the end(NULL CHAR)and displays a char each time.

 ***************************************************************************************************/
#if (Enable_GLCD_DisplayString==1)
void GLCD_DisplayString(char *ptr_stringPointer_u8)
{
    while((*ptr_stringPointer_u8)!=0)
        GLCD_DisplayChar(*ptr_stringPointer_u8++); // Loop through the string and display char by char
}
#endif







/***************************************************************************************************
               void GLCD_ScrollMessage(uint8_t var_lineNumber_u8, char *ptr_msgPointer_u8)
 ***************************************************************************************************
 * I/P Arguments: 
                  uint8_t  : Line number on which the message has to be scrolled
                  char *: pointer to the string to be scrolled                      

 * Return value    : none

 * description  :This function scrolls the given message on the specified line.
                 If the specified line number is out of range then the message
                 will be scrolled on first line
 ***************************************************************************************************/
#if ( Enable_GLCD_ScrollMessage  == 1 )
void GLCD_ScrollMessage(uint8_t var_lineNumber_u8, char *ptr_msgPointer_u8)
{
    unsigned char i,j;


    if(var_lineNumber_u8 > STK_LCDConfig.mvar_MaxSupportedLines_U8)
        var_lineNumber_u8 = mENUM_GlcdLineOne; // Select first line if the var_lineNumber_u8 is out of range

    glcd_CmdWrite(CMD_DISPLAY_ON_CURSOR_OFF);             //Disable the Cursor

    for(i=0;ptr_msgPointer_u8[i];i++)
    {      
        /* Loop to display the complete string,    each time 16 chars are displayed and
        pointer is incremented to point to next char */


        GLCD_GoToLine(var_lineNumber_u8);     //Move the Cursor to first line

        for(j=0;j<STK_LCDConfig.mvar_MaxSupportedChars_U8 && ptr_msgPointer_u8[i+j];j++)
        {
            //Display first 16 Chars or till Null char is reached
            GLCD_DisplayChar(ptr_msgPointer_u8[i+j]);
        }


        while( j<STK_LCDConfig.mvar_MaxSupportedChars_U8)
        {
            /*If the chars to be scrolled are less than MaxLcdChars,
              then display remaining chars with blank spaces*/
            GLCD_DisplayChar(' ');
            j++;
        }

        DELAY_ms(125);
    }
    glcd_CmdWrite(CMD_DISPLAY_ON_CURSOR_ON);              // Finally enable the Cursor
}
#endif



/***************************************************************************************************
void GLCD_DisplayNumber(NumericSystem_et e_typeOfNum_e8, uint32_t var_number_u32, uint8_t var_numOfDigitsToDisplay_u8)
 ***************************************************************************************************
 * Function name:  GLCD_DisplayNumber()
 * I/P Arguments: 
                  NumericSystem_et :  specifies type of number ENUM_BINARY(2),ENUM_DECIMAL(10), ENUM_Hex(16)
                  uint32_t: Number to be displayed on the glcdConfig.
                  uint8_t : Number of digits to be displayed

 * Return value	: none

 * description  :This function is used to display a max of 10digit decimal/Hex number OR specified 
                 number of bits for binary number.

                1st parameter specifies type of number ENUM_BINARY(2),ENUM_DECIMAL(10), ENUM_Hex(16)                  
                3rd parameter specifies the number of digits from the right side to be displayed
                 The output for the input combinations is as below

    Binary:     1.(10,4) then 4-LSB will be displayed ie. 1010
				2.(10,8) then 8-LSB will be displayed ie. 00001010
				3.(10,2) then 2-LSB will be displayed ie. 10

    Decimal:    4.(10,12345,4) then 4-digits ie. 2345 will be displayed
				5.(ENUM_DECIMAL,12345,6) then 6-digits ie. 012345 will be displayed
				6.(10,12345,C_DisplayDefaultDigits_U8) then 12345 will be displayed.\

    Hex:        7.(16,0x12AB,3) then 3-digits ie. 2AB will be displayed
				8.(ENUM_Hex,0x12AB,6) then 6-digits ie. 0012AB will be displayed
				9.(ENUM_Hex,0x12AB,C_DisplayDefaultDigits_U8) then 12AB will be displayed.                
 ***************************************************************************************************/
#if ((Enable_GLCD_DisplayNumber == 1) || (Enable_GLCD_DisplayFloatNumber == 1) || (ENABLE_GLCD_Printf==1))
void GLCD_DisplayNumber(NumericSystem_et enm_typeOfNumber, uint32_t var_number_u32, uint8_t var_numOfDigitsToDisplay_u8)
{
    uint8_t i=0,a[10];

    if(E_BINARY == enm_typeOfNumber)
    {
        while(var_numOfDigitsToDisplay_u8!=0)
        {
            /* Start Extracting the bits from the specified bit positions.
	      Get the Acsii values of the bits and display */
            i = util_GetBitStatus(var_number_u32,(var_numOfDigitsToDisplay_u8-1));
            GLCD_DisplayChar(util_Dec2Ascii(i));
            var_numOfDigitsToDisplay_u8--;
        }
    }    
    else if(var_number_u32==0)
    {
        /* If the number is zero then update the array with the same for displaying */
        for(i=0;((i<var_numOfDigitsToDisplay_u8) && (i<C_MaxDigitsToDisplay_U8));i++)
            GLCD_DisplayChar('0');
    }
    else
    {
        for(i=0;i<var_numOfDigitsToDisplay_u8;i++)
        {
            /* Continue extracting the digits from right side
			   till the Specified var_numOfDigitsToDisplay_u8 */
            if(var_number_u32!=0)
            {
                /* Extract the digits from the number till it becomes zero.
			    First get the remainder and divide the number by TypeOfNum(10-Dec, 16-Hex) each time.

                example for Decimal number: 
                If var_number_u32 = 123 then extracted remainder will be 3 and number will be 12.
				The process continues till it becomes zero or max digits reached*/
                a[i]=util_GetMod32(var_number_u32,enm_typeOfNumber);
                var_number_u32=var_number_u32/enm_typeOfNumber;
            }
            else if( (var_numOfDigitsToDisplay_u8 == C_DisplayDefaultDigits_U8) ||
                    (var_numOfDigitsToDisplay_u8 > C_MaxDigitsToDisplay_U8))
            {
                /* Stop the iteration if the Max number of digits are reached or
			     the user expects exact(Default) digits in the number to be displayed */ 
                break;
            }
            else
            {
                /* In case user expects more digits to be displayed than the actual digits in number,
  			    then update the remaining digits with zero.
               Ex: var_num_u32 is 123 and user wants five digits then 00123 has to be displayed */
                a[i]=0;
            }
        }

        while(i!=0)
        {
            /* Finally get the ascii values of the digits and display*/
            GLCD_DisplayChar(util_Hex2Ascii(a[i-1]));
            i--;
        }
    }
}
#endif








/*************************************************************************************************
            void  GLCD_DisplayFloatNumber(double var_floatNum_f32)
 *************************************************************************************************
 * Function name:  GLCD_DisplayFloatNumber()
 * I/P Arguments: float: float Number to be displayed on the LCD.

 * Return value	: none

 * description  :This function is used to display a floating point number
                 It supports 6digits of precision.

    Note: Float will be disabled by default as it takes huge controller resources
	     It can be enabled by changing value of Enable_GLCD_DisplayFloatNumber to 1 in lcd.h
 **************************************************************************************************/
#if (Enable_GLCD_DisplayFloatNumber == 1)  
void GLCD_DisplayFloatNumber(double var_floatNum_f32)
{
    uint32_t var_temp_u32;
    /* Dirty hack to support the floating point by extracting the integer and fractional part.
      1.Type cast the number to int to get the integer part.
	  2.Display the extracted integer part followed by a decimal point(.)
	  3.Later the integer part is made zero by subtracting with the extracted integer value.
	  4.Finally the fractional part is multiplied by 100000 to support 6-digit precision */

    var_temp_u32 = (uint32_t) var_floatNum_f32;
    GLCD_DisplayNumber(E_DECIMAL,var_temp_u32,C_DisplayDefaultDigits_U8);

    GLCD_DisplayChar('.');

    var_floatNum_f32 = var_floatNum_f32 - var_temp_u32;
    var_temp_u32 = var_floatNum_f32 * 1000000;
    GLCD_DisplayNumber(E_DECIMAL,var_temp_u32,C_DisplayDefaultDigits_U8);
}
#endif






/*************************************************************************************************
            void GLCD_Printf(const char *argList, ...)
 *************************************************************************************************
 * Function name:  GLCD_Printf()
 * I/P Arguments: variable length arguments similar to printf

 * Return value	: none

 * description  :This function is similar to printf function in C.
				 It takes the arguments with specified format and prints accordingly
				 The supported format specifiers are as below.
				 1. %c: character
				 2. %d: signed 16-bit number
				 3. %D: signed 32-bit number
				 4. %u: unsigned 16-bit number
				 5. %U: unsigned 32-bit number
				 6. %b: 16-bit binary number
				 7. %B: 32-bit binary number
				 8. %f: Float number
				 9. %x: 16-bit hexadecimal number
				 10. %X: 32-bit hexadecimal number
				 11. %s: String



  Extra feature is available to specify the number of digits to be displayed using printf.
	 ex: %4d: will display the lower four digits of the decimal number.
	     %12b: will display the 12-LSB of the number
		 %d: Will display the exact digits of the number

#####: In case of printing the 8-bit variables, it is recommended to type cast and promote them to uint16_t.
        uint8_t var_Num_u8;
		GLCD_Printf("num1:%u",(uint16_t)var_Num_u8); 
 *************************************************************************************************/
#if ( Enable_GLCD_Printf   == 1 ) 
void GLCD_Printf(const char *argList, ...)
{
    const char *ptr;
    va_list argp;
    sint16_t var_num_s16;
    sint32_t var_num_s32;
    uint16_t var_num_u16;
    uint32_t var_num_u32;
    char *str;
    char  ch;
    uint8_t var_numOfDigitsToDisp_u8;
#ifdef Enable_GLCD_DisplayFloatNumber
    double var_floatNum_f32;
#endif

    va_start(argp, argList);

    /* Loop through the list to extract all the input arguments */
    for(ptr = argList; *ptr != '\0'; ptr++)
    {

        ch= *ptr;
        if(ch == '%')         /*Check for '%' as there will be format specifier after it */
        {
            ptr++;
            ch = *ptr;
            if((ch>=0x30) && (ch<=0x39))
            {
                var_numOfDigitsToDisp_u8 = 0;
                while((ch>=0x30) && (ch<=0x39))
                {
                    var_numOfDigitsToDisp_u8 = (var_numOfDigitsToDisp_u8 * 10) + (ch-0x30);
                    ptr++;
                    ch = *ptr;
                }
            }
            else
            {
                var_numOfDigitsToDisp_u8 = C_MaxDigitsToDisplayUsingPrintf_U8;
            }                


            switch(ch)       /* Decode the type of the argument */
            {
            case 'C':
            case 'c':     /* Argument type is of char, hence read char data from the argp */
                ch = va_arg(argp, int);
                GLCD_DisplayChar(ch);
                break;

            case 'd':    /* Argument type is of signed integer, hence read 16bit data from the argp */
                var_num_s16 = va_arg(argp, int);
#if (Enable_GLCD_DisplayNumber == 1)
                if(var_num_s16<0)
                { /* If the number is -ve then display the 2's complement along with '-' sign */
                    var_num_s16 = -var_num_s16;
                    GLCD_DisplayChar('-');
                }
                GLCD_DisplayNumber(E_DECIMAL,var_num_s16,var_numOfDigitsToDisp_u8);
#endif
                break;

            case 'D':    /* Argument type is of integer, hence read 16bit data from the argp */
#if (Enable_GLCD_DisplayNumber == 1)
                var_num_s32 = va_arg(argp, sint32_t);
                if(var_num_s32<0)
                { /* If the number is -ve then display the 2's complement along with '-' sign */
                    var_num_s32 = -var_num_s32;
                    GLCD_DisplayChar('-');
                }
                GLCD_DisplayNumber(E_DECIMAL,var_num_s32,var_numOfDigitsToDisp_u8);
#endif                
                break;    

            case 'u':    /* Argument type is of unsigned integer, hence read 16bit unsigned data */
                var_num_u16 = va_arg(argp, int);
#if (Enable_GLCD_DisplayNumber == 1)
                GLCD_DisplayNumber(E_DECIMAL,var_num_u16,var_numOfDigitsToDisp_u8);
#endif                
                break;

            case 'U':    /* Argument type is of integer, hence read 32bit unsigend data */
                var_num_u32 = va_arg(argp, uint32_t);
#if (Enable_GLCD_DisplayNumber == 1)
                GLCD_DisplayNumber(E_DECIMAL,var_num_u32,var_numOfDigitsToDisp_u8);
#endif                
                break;            

            case 'x':  /* Argument type is of hex, hence hexadecimal data from the argp */
                var_num_u16 = va_arg(argp, int);
#if (Enable_GLCD_DisplayNumber == 1)
                GLCD_DisplayNumber(E_HEX,var_num_u16,var_numOfDigitsToDisp_u8);
#endif                
                break;

            case 'X':  /* Argument type is of hex, hence hexadecimal data from the argp */
                var_num_u32 = va_arg(argp, uint32_t);
#if (Enable_GLCD_DisplayNumber == 1)
                GLCD_DisplayNumber(E_HEX,var_num_u32,var_numOfDigitsToDisp_u8);
#endif                
                break;


            case 'b':  /* Argument type is of binary,Read int and convert to binary */
                var_num_u16 = va_arg(argp, int);
#if (Enable_GLCD_DisplayNumber == 1)
                if(var_numOfDigitsToDisp_u8 == C_MaxDigitsToDisplayUsingPrintf_U8)
                    var_numOfDigitsToDisp_u8 = 16;
                GLCD_DisplayNumber(E_BINARY,var_num_u16,var_numOfDigitsToDisp_u8);
#endif                
                break;

            case 'B':  /* Argument type is of binary,Read int and convert to binary */
                var_num_u32 = va_arg(argp, uint32_t);
#if (Enable_GLCD_DisplayNumber == 1)
                if(var_numOfDigitsToDisp_u8 == C_MaxDigitsToDisplayUsingPrintf_U8)
                    var_numOfDigitsToDisp_u8 = 16;
                GLCD_DisplayNumber(E_BINARY,var_num_u32,var_numOfDigitsToDisp_u8);
#endif                
                break;


            case 'F':
            case 'f': /* Argument type is of float, hence read double data from the argp */
                var_floatNum_f32 = va_arg(argp, double);
#if (Enable_GLCD_DisplayFloatNumber == 1)                
                GLCD_DisplayFloatNumber(var_floatNum_f32);
#endif
                break;


            case 'S':
            case 's': /* Argument type is of string, hence get the pointer to sting passed */
                str = va_arg(argp, char *);
#if (Enable_GLCD_DisplayString == 1)
                GLCD_DisplayString(str);
#endif                
                break;

            case '%':
                GLCD_DisplayChar('%');
                break;
            }
        }
        else
        {
            /* As '%' is not detected display/transmit the char passed */
            GLCD_DisplayChar(ch);
        }
    }

    va_end(argp);
}
#endif













#if (ENABLE_GLCD_DisplayLogo ==1)
void GLCD_DisplayLogo()
{
    uint8_t line,cursor;

    for(line=0;line<8;line++)
    {
        glcd_SelectPage0();
        glcd_CmdWrite(0x40);
        glcd_CmdWrite(C_FirstLineNumberAddress_U8+line);
        for(cursor=0;cursor<128;cursor++)
        {
            if(cursor==64)
            {
                glcd_SelectPage1();
                glcd_CmdWrite(0x40);
                glcd_CmdWrite(C_FirstLineNumberAddress_U8+line);
            }
            glcd_DataWrite(0x00);
        }
    }

    GLCD_GoToLine(0);
}
#endif






/**************************************************************************************************
								void GLCD_GetXYData()
 ***************************************************************************************************
 * I/P Arguments:  var_x_u8 : x coordinate of point	(0 to 127)
 				   var_y_u8 : y coordinate of point	(0 to 63)
				   var_length_u8: length of line
				   var_color_u8	 : color of pixels
 * Return value	: uint8_t v_dataRead_u8 at on GLCD line having point(x,y) 

 * description  :This function is used to read v_dataRead_u8 on GLCD line having point(x,y)
 **************************************************************************************************/
#if (ENABLE_GLCD_GetXYData ==1)
uint8_t GLCD_GetXYData(uint8_t var_x_u8, uint8_t var_y_u8)
{
    uint8_t v_dataRead_u8 = 0;

    if ((var_x_u8<128)&&(var_y_u8<64))	  // check for valid coordinates
    {
        if(var_x_u8 > 63) 			// set the variables values page & cursor position
        {
            glcd_SelectPage1();
            glcdConfig.PageNum=1;
            glcdConfig.CursorPos= var_x_u8-64;
        }
        else
        {
            glcd_SelectPage0();
            glcdConfig.PageNum=0;
            glcdConfig.CursorPos= var_x_u8 ;
        }

        glcdConfig.LineNum=C_FirstLineNumberAddress_U8 + (var_y_u8 >> 3);	   // get line no.
        GLCD_SetCursor(glcdConfig.PageNum,glcdConfig.LineNum,glcdConfig.CursorPos);


        //	v_dataRead_u8 = GLCD_DataRead();			//dummy read
        v_dataRead_u8 = GLCD_DataRead();
    }
    return (v_dataRead_u8);
}
#endif



/***************************************************************************************************
                       void GLCD_DataRead( )
 ***************************************************************************************************
 * I/P Arguments: none
 * Return value	: returns 8 bit v_dataRead_u8

 * description : This functions is used to read v_dataRead_u8 at current cursor position on GLCD

 ***************************************************************************************************/
#if (ENABLE_GLCD_DataRead ==1) 
uint8_t GLCD_DataRead(void)
{
    uint8_t v_dataRead_u8;

    v_dataRead_u8 = shadowBuffer[glcdConfig.LineNum-C_FirstLineNumberAddress_U8][(glcdConfig.PageNum*64)+glcdConfig.CursorPos];

    return(v_dataRead_u8);
}
#endif


/**************************************************************************************************
								void GLCD_SetDot()
 ***************************************************************************************************
 * I/P Arguments:  var_x_u8 : x coordinate of point	(0 to 127)
 				   var_y_u8 : y coordinate of point	(0 to 63)
				   var_color_u8	 : color of pixels
 * Return value	: none

 * description  :This function is used to draw a dot
 **************************************************************************************************/
#if (ENABLE_GLCD_SetDot ==1)
void GLCD_SetDot(uint8_t var_x_u8, uint8_t var_y_u8, uint8_t var_color_u8)
{
    uint8_t v_dataRead_u8;

    if ((var_x_u8<128)&&(var_y_u8<64))				 // check for valid coordinates
    {
        v_dataRead_u8 = GLCD_GetXYData(var_x_u8,var_y_u8);	 // read GLCD v_dataRead_u8

        var_y_u8 = util_GetMod8(var_y_u8,8);		 // get line offset

        if (var_color_u8)							// update the bit at the offset position
            util_BitSet(v_dataRead_u8,var_y_u8);
        else
            util_BitClear(v_dataRead_u8,var_y_u8);

        glcd_DataWrite(v_dataRead_u8^glcdConfig.InvertDisplay);
    }

}
#endif


/**************************************************************************************************
								void GLCD_DrawHoriLine()
 ***************************************************************************************************
 * I/P Arguments:  var_x_u8 : x coordinate of left side end point of line	(0 to 127)
 				   var_y_u8 : y coordinate of left side end point of line	(0 to 63)
				   var_length_u8: length of line
				   var_color_u8	 : color of pixels
 * Return value	: none

 * description  :This function is used to draw horizontial line
 **************************************************************************************************/
#if (ENABLE_GLCD_DrawHoriLine == 1)
void GLCD_DrawHoriLine(uint8_t var_x_u8, uint8_t var_y_u8, uint8_t var_length_u8,uint8_t var_color_u8)
{

    if ((var_x_u8<128)&&(var_y_u8<64))					 // check for valid coordinates
    {
        var_length_u8++;
        while(var_length_u8)
        {
            GLCD_SetDot(var_x_u8,var_y_u8,var_color_u8);

            if ((glcdConfig.CursorPos >0x7F) && (glcdConfig.PageNum == 1)) // end of GLCD is reached
                return;		   								 // truncate the line

            var_x_u8++;
            var_length_u8--;
        }
    }


}
#endif



/**************************************************************************************************
								void GLCD_DrawVertLine()
 ***************************************************************************************************
 * I/P Arguments:  var_x_u8 : x coordinate of top side end point of line	(0 to 127)
 				   var_y_u8 : y coordinate of top side end point of line	(0 to 63)
				   var_length_u8: length of line
				   var_color_u8	 : color of pixels
 * Return value	: none

 * description  :This function is used to draw vertical line
 **************************************************************************************************/

/*
 	TO DO
 	if end of display is reached and still length is not zero
	control should out of function GLCD_DrawVertLine()
 */
#if ((ENABLE_GLCD_DrawVertLine ==1) || (ENABLE_GLCD_DrawLine==1))
void GLCD_DrawVertLine(uint8_t var_x_u8, uint8_t var_y_u8, uint8_t var_length_u8, uint8_t var_color_u8)
{

    if ((var_x_u8<128)&&(var_y_u8<64))				 // check for valid coordinates
    {
        while(var_length_u8)
        {
            GLCD_SetDot(var_x_u8,var_y_u8,var_color_u8);

            if (glcdConfig.LineNum > C_LastLineNumberAddress_U8)	   // end of dispaly
                return;

            var_y_u8++;
            var_length_u8--;            
        }
    }

}
#endif



/**************************************************************************************************
								void GLCD_DrawLine()
 ***************************************************************************************************
 * I/P Arguments:  var_x1_u8 : x coordinate of end point of line	(0 to 127)
 				   var_y1_u8 : y coordinate of end point of line	(0 to 63)
				   var_x2_u8: x coordinate of other end point of line
				   var_y2_u8: y coordinate of other end point of line
				   var_color_u8	 : color of pixels
 * Return value	: none

 * description  :This function is used to draw line
 **************************************************************************************************/
#if (ENABLE_GLCD_DrawLine ==1)
void GLCD_DrawLine(uint8_t var_x1_u8, uint8_t var_y1_u8, uint8_t var_x2_u8, uint8_t var_y2_u8, uint8_t var_color_u8)
{
    uint8_t  deltax, deltay, x_len,y_len, step;
    sint8_t lerror, ystep;

    x_len= util_GetAbsolute(var_x1_u8 - var_x2_u8);
    y_len= util_GetAbsolute(var_y1_u8 - var_y2_u8);

    if ((var_x1_u8<128)&&(var_x2_u8<128)&&(var_y1_u8<64)&&(var_y2_u8<64))	 // check for valid coordinates
    {

        // check if line is horizontial, vertical or slant
        if(var_x1_u8 == var_x2_u8)
        {
            GLCD_DrawVertLine(var_x1_u8, var_y1_u8, y_len, var_color_u8);
            return;
        }
        else if(var_y1_u8 == var_y2_u8)
        {
            GLCD_DrawHoriLine(var_x1_u8, var_y1_u8, x_len, var_color_u8);
            return;
        }

        // draw the slant line
        step = y_len>x_len;   //check slope

        if ( step )
        {
            util_swap(var_x1_u8, var_y1_u8);
            util_swap(var_x2_u8, var_y2_u8);
        }

        if (var_x1_u8 > var_x2_u8)
        {
            util_swap(var_x1_u8, var_x2_u8);
            util_swap(var_y1_u8, var_y2_u8);
        }

        deltax = var_x2_u8 - var_x1_u8;
        deltay = util_GetAbsolute(var_y2_u8 - var_y1_u8);
        lerror = deltax / 2;
        y_len = var_y1_u8;

        if(var_y1_u8 < var_y2_u8)
            ystep = 1;
        else
            ystep = -1;

        for(x_len = var_x1_u8; x_len <= var_x2_u8; x_len++)
        {
            if (step)
                GLCD_SetDot(y_len,x_len,var_color_u8);
            else
                GLCD_SetDot(x_len,y_len,var_color_u8);

            lerror -= deltay;

            if (lerror < 0)
            {
                y_len += ystep;
                lerror += deltax;
            }
        }
    }
}
#endif



/**************************************************************************************************
								void GLCD_DrawRect()
 ***************************************************************************************************
 * I/P Arguments:  var_x_u8 : x coordinate of top left side vertex of rectangle	(0 to 127)
 				   var_y_u8 : y coordinate of top left side vertex of rectangle	(0 to 63)
				   var_width_u8 : width of rectangle
				   var_height_u8 : height of rectangle
				   var_color_u8	 : color of pixels
 * Return value	: none

 * description  :This function is used to draw rectangle
 **************************************************************************************************/
#if (ENABLE_GLCD_DrawRect ==1)
void GLCD_DrawRect(uint8_t var_x_u8, uint8_t var_y_u8, uint8_t var_width_u8, uint8_t var_height_u8, uint8_t var_color_u8) 
{
    if ((var_x_u8<128)&&(var_y_u8<64))	  // check for valid coordinates
    {
        GLCD_DrawHoriLine(var_x_u8, var_y_u8, var_width_u8, var_color_u8);			 		 //top
        GLCD_DrawHoriLine(var_x_u8, var_y_u8 + var_height_u8, var_width_u8, var_color_u8);	 //bottom
        GLCD_DrawVertLine(var_x_u8, var_y_u8, var_height_u8, var_color_u8);		 			 //left
        GLCD_DrawVertLine(var_x_u8 + var_width_u8, var_y_u8, var_height_u8, var_color_u8);	 //right
    }
    return;
}
#endif



/**************************************************************************************************
								void GLCD_DrawFillRect()
 ***************************************************************************************************
 * I/P Arguments:  var_x_u8 : x coordinate of top left side vertex of rectangle	(0 to 127)
 				   var_y_u8 : y coordinate of top left side vertex of rectangle	(0 to 63)
				   var_width_u8 : width of rectangle
				   var_height_u8 : height of rectangle
				   var_color_u8	 : color of pixels
 * Return value	: none

 * description  :This function is used to draw filled rectangle
 **************************************************************************************************/
#if (ENABLE_GLCD_DrawFillRect ==1)
void GLCD_DrawFillRect(uint8_t var_x_u8, uint8_t var_y_u8, uint8_t var_width_u8, uint8_t var_height_u8, uint8_t var_color_u8) 
{
    uint8_t temp;

    if ((var_x_u8<128)&&(var_y_u8<64))		 // check for valid coordinates
    {
        temp = var_y_u8 + var_height_u8;

        while(var_y_u8 <= temp)
        {
            GLCD_DrawHoriLine(var_x_u8, var_y_u8, var_width_u8, var_color_u8);
            var_y_u8++;
        }
    }
    return;
}
#endif



/**************************************************************************************************
								void GLCD_DrawRoundRect()
 ***************************************************************************************************
 * I/P Arguments:  var_x_u8 : x coordinate of top left side vertex of rectangle	(0 to 127)
 				   var_y_u8 : y coordinate of top left side vertex of rectangle	(0 to 63)
				   var_width_u8 : width of rectangle
				   var_height_u8 : height of rectangle
				   var_radius_u8 : radius of circular part at corner
				   var_color_u8	 : color of pixels
 * Return value	: none

 * description  :This function is used to draw rectangle with round corners
 **************************************************************************************************/
#if (ENABLE_GLCD_DrawRoundRect ==1)
void GLCD_DrawRoundRect(uint8_t var_x_u8, uint8_t var_y_u8, uint8_t var_width_u8, uint8_t var_height_u8, uint8_t var_radius_u8, uint8_t var_color_u8) 
{
    int step, x1 = 0, y1 = var_radius_u8;

    step = 3 - 2 * var_radius_u8;

    if ((var_x_u8<128)&&(var_y_u8<64))		 // check for valid coordinates
    {
        while (x1 <= y1)
        {
            GLCD_SetDot(var_x_u8 + var_radius_u8 - x1, var_y_u8 + var_radius_u8 - y1, var_color_u8);
            GLCD_SetDot(var_x_u8 + var_radius_u8 - y1, var_y_u8 + var_radius_u8 - x1, var_color_u8);

            GLCD_SetDot(var_x_u8 + var_width_u8 - var_radius_u8 + x1, var_y_u8 + var_radius_u8 - y1, var_color_u8);
            GLCD_SetDot(var_x_u8 + var_width_u8 - var_radius_u8 + y1, var_y_u8 + var_radius_u8 - x1, var_color_u8);

            GLCD_SetDot(var_x_u8 + var_width_u8 - var_radius_u8 + x1, var_y_u8 + var_height_u8 - var_radius_u8 + y1, var_color_u8);
            GLCD_SetDot(var_x_u8 + var_width_u8 - var_radius_u8 + y1, var_y_u8 + var_height_u8 - var_radius_u8 + x1, var_color_u8);

            GLCD_SetDot(var_x_u8 + var_radius_u8 - x1, var_y_u8 + var_height_u8 - var_radius_u8 + y1, var_color_u8);
            GLCD_SetDot(var_x_u8 + var_radius_u8 - y1, var_y_u8 + var_height_u8 - var_radius_u8 + x1, var_color_u8);

            if (step < 0)
            {
                step += (4 * x1 + 6);
            }
            else
            {
                step += (4 * (x1 - y1) + 10);
                y1--;
            }
            x1++;
        }

        GLCD_DrawHoriLine(var_x_u8 + var_radius_u8, var_y_u8, var_width_u8 -(2*var_radius_u8), var_color_u8);                // top
        GLCD_DrawHoriLine(var_x_u8 + var_radius_u8, var_y_u8 + var_height_u8, var_width_u8-(2*var_radius_u8), var_color_u8);   // bottom
        GLCD_DrawVertLine(var_x_u8, var_y_u8 + var_radius_u8,var_height_u8 -(2*var_radius_u8), var_color_u8);                	// left
        GLCD_DrawVertLine(var_x_u8 + var_width_u8, var_y_u8 + var_radius_u8,var_height_u8-(2*var_radius_u8), var_color_u8);    // right
    }
}
#endif



/**************************************************************************************************
								void GLCD_InvertRect()
 ***************************************************************************************************
 * I/P Arguments:  var_x_u8 : x coordinate of top left side vertex of rectangle	(0 to 127)
 				   var_y_u8 : y coordinate of top left side vertex of rectangle	(0 to 63)
				   var_width_u8 : width of rectangle
				   var_height_u8 : height of rectangle
 * Return value	: none

 * description  :This function is used to inevert the selected rectangular area
 **************************************************************************************************/
#if (ENABLE_GLCD_InvertRect ==1)
void GLCD_InvertRect(uint8_t var_x_u8, uint8_t var_y_u8, uint8_t var_width_u8, uint8_t var_height_u8)
{
    uint8_t v_dataRead_u8,tempX,tempY,LineOffset;

    if ((var_x_u8<128)&&(var_y_u8<64))		   // check for valid coordinates
    {
        for(tempX=var_x_u8; tempX<=(var_x_u8 + var_width_u8); tempX++)
        {
            for(tempY=var_y_u8; tempY<=(var_y_u8+var_height_u8); tempY++)
            {
                v_dataRead_u8 = GLCD_GetXYData(tempX,tempY);
                LineOffset = util_GetMod8(tempY,8);
                util_BitToggle(v_dataRead_u8,LineOffset);
                glcd_DataWrite(v_dataRead_u8^glcdConfig.InvertDisplay);
            }
        }
    }
    return;
}
#endif



#if (ENABLE_GLCD_DisplayVerticalGraph ==1)
void GLCD_DisplayVerticalGraph(uint8_t var_barGraphNumber_u8, uint8_t var_percentageValue_u8)
{
    uint8_t var_lineNumberToStartDisplay_u8,i,j,var_barGraphPosition_u8;
    uint8_t lineNumber,var_valueToDisplay_u8,var_page_u8;

    /* TODO: Finalize the graph numbers */
    if((var_barGraphNumber_u8 < C_MaxBarGraphs_U8) && (var_percentageValue_u8<=100))
    {
        var_barGraphPosition_u8 = var_barGraphNumber_u8 * 32;

        if(var_barGraphPosition_u8<64)
        {
            var_page_u8 = 0;
        }
        else
        {
            var_page_u8 = 1;
            var_barGraphPosition_u8 = var_barGraphPosition_u8 - 64;
        }


        GLCD_SetCursor(var_page_u8,0,var_barGraphPosition_u8+8);
        GLCD_DisplayNumber(E_DECIMAL,var_percentageValue_u8,3);


        /* Divide the value by 8, as we have 8-pixels for each line */
        var_percentageValue_u8 = var_percentageValue_u8/2;
        var_lineNumberToStartDisplay_u8 = (var_percentageValue_u8>>3);
        lineNumber = 7-var_lineNumberToStartDisplay_u8;


        for(i=1;i<8;i++) /* TODO: Finalize the line coding */
        {
            GLCD_SetCursor(var_page_u8,i,(var_barGraphPosition_u8+12));
            if(i<lineNumber)
            {
                var_valueToDisplay_u8 = 0x00;
            }
            else if(i== lineNumber)
            {
                var_valueToDisplay_u8 = util_GetMod8(var_percentageValue_u8,8);
                var_valueToDisplay_u8 = (0xff<<(8-var_valueToDisplay_u8));
            }
            else
            {
                var_valueToDisplay_u8 = 0xff;
            }

            for(j=0;j<12;j++)
            {

                glcd_DataWrite(var_valueToDisplay_u8);
            }
        }
    }
}
#endif


#if (ENABLE_GLCD_DisplayHorizontalGraph ==1)
void GLCD_DisplayHorizontalGraph(uint8_t var_barGraphNumber_u8, uint8_t var_percentageValue_u8)
{
    uint8_t var_lineNumber_u8,i;
    var_lineNumber_u8 = (var_barGraphNumber_u8 * 2)+1;

    if((var_barGraphNumber_u8 < C_MaxBarGraphs_U8) && (var_percentageValue_u8<=100))
    {

        GLCD_SetCursor(0,var_lineNumber_u8,0);

        for(i=0;i<var_percentageValue_u8;i++)
        {
            if(i==64)
                GLCD_GoToPage(1);

            glcd_DataWrite(0xff);

        }

        for(i=var_percentageValue_u8;i<100;i++)
        {
            if(i==64)
                GLCD_GoToPage(1);

            glcd_DataWrite(0x00);
        }

        GLCD_SetCursor(1,var_lineNumber_u8,110);

        GLCD_DisplayNumber(E_DECIMAL,var_percentageValue_u8,3);
    }
}
#endif
/**************************************************************************************************
								void GLCD_DrawCircle()
 ***************************************************************************************************
 * I/P Arguments:  var_x_u8 : x coordinate of center of circle	(0 to 127)
 				   var_y_u8 : y coordinate of center of circle	(0 to 63)
				   var_radius_u8 : radius of circle
				   var_color_u8 : color of dots
 * Return value	: none

 * description  :This function is used to draw a circle
 **************************************************************************************************/
#if (ENABLE_GLCD_DrawCircle ==1)
void GLCD_DrawCircle(uint8_t var_x_u8, uint8_t var_y_u8, uint8_t var_radius_u8, uint8_t var_color_u8) 
{
    unsigned int tempY = 0, tempX = 0, d = 0;
    int step;

    if ((var_x_u8<128)&&(var_y_u8<64))		 // check for valid coordinates
    {

        d = var_y_u8 - var_x_u8;
        tempY = var_radius_u8;
        step = 3 - 2 * var_radius_u8;

        while (tempX <= tempY)
        {
            GLCD_SetDot(var_x_u8 + tempX, var_y_u8 + tempY, var_color_u8);
            GLCD_SetDot(var_x_u8 + tempX, var_y_u8 - tempY, var_color_u8);
            GLCD_SetDot(var_x_u8 - tempX, var_y_u8 + tempY, var_color_u8);
            GLCD_SetDot(var_x_u8 - tempX, var_y_u8 - tempY, var_color_u8);
            GLCD_SetDot(var_y_u8 + tempY - d, var_y_u8 + tempX, var_color_u8);
            GLCD_SetDot(var_y_u8 + tempY - d, var_y_u8 - tempX, var_color_u8);
            GLCD_SetDot(var_y_u8 - tempY - d, var_y_u8 + tempX, var_color_u8);
            GLCD_SetDot(var_y_u8 - tempY - d, var_y_u8 - tempX, var_color_u8);

            if (step < 0)
                step += (4 * tempX + 6);
            else
            {
                step += (4 * (tempX - tempY) + 10);
                tempY--;
            }
            tempX++;
        }
    }
}
#endif



/**************************************************************************************************
								void GLCD_DrawFillCircle()
 ***************************************************************************************************
 * I/P Arguments:  var_x_u8 : x coordinate of center of circle	(0 to 127)
 				   var_y_u8 : y coordinate of center of circle	(0 to 63)
				   var_radius_u8 : radius of circle
				   var_color_u8 : color of dots
 * Return value	: none

 * description  :This function is used to draw a filled circle
 **************************************************************************************************/
#if (ENABLE_GLCD_DrawFillCircle ==1)
void GLCD_DrawFillCircle(uint8_t var_x_u8, uint8_t var_y_u8, uint8_t var_radius_u8, uint8_t var_color_u8) 
{
    if((var_x_u8 < 128) && (var_y_u8 < 63))		  // check for valid coordinates
    {
        while(var_radius_u8)
        {
            GLCD_DrawCircle(var_x_u8, var_y_u8, var_radius_u8, var_color_u8);
            var_radius_u8--;
        }
    }
    return;
}
#endif
