/***************************************************************************************************
                                   ExploreEmbedded
 ****************************************************************************************************
 * File:   main.c
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: This file contains the program to the on board peripherals of ExploreLpc2148 board. 

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the
library works on any of development boards for respective controllers. However, ExploreEmbedded
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information
related to updates.


GNU GENERAL PUBLIC LICENSE:
    Copyright (C) 2012  ExploreEmbedded

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
 **************************************************************************************************/

#include "adc.h"
#include "delay.h"
#include "gpio.h"
#include "lcd.h"
#include "stdutils.h"
#include "uart.h"
#include "rtc.h"
#include "pwm.h"


#define SWITCH1 P0_14
#define SWITCH2 P0_7
#define SWITCH3 P0_15
#define LED1 P1_20
#define LED2 P1_21
#define LED3 P1_22
#define LED4 P1_23



void led_Test(void);
void switch_Test(void);
void gpio_Test(void);
void lcd_Test(void);
void adc_Test(void);
void pwm_Test(void);
void uart1_test(void);
void rtc_Test(void);

int main() 
{

    char option; 
    SystemInit();

    GPIO_PinDirection(SWITCH2,INPUT);
    
    if(GPIO_PinRead(SWITCH2)) // Testing Not required, Just blink Leds
        led_Test();

    UART0_Init(9600);
    UART0_Printf("\n\r\n\rExplore LPC1768 Test Menu\n\r "
            "1.Led test\n\r "
            "2.Switch test\n\r "
            "3.GPIO test\n\r "    
            "4.Lcd test\n\r "
            "5.Adc Test\n\r "
            "6.RTC Test\n\r "
            "7.PWM Test\n\r "    
            "Select One of the above options");

    while(1)
    {
        option = UART0_RxChar();
        switch(option)
        {
        case '1':
            led_Test();
            break;

        case '2':
            switch_Test();
            break;

        case '3':
            gpio_Test();
            break;

        case '4':
            lcd_Test();
            break;


        case '5':
            adc_Test();
            break;

        case '6':
            rtc_Test();
            break;    

        case '7':
            pwm_Test();
            break;

        default:
            break;    
        }
    }
}


void led_Test(void)
{
    uint8_t i;

    for(i=LED1;i<=LED4;i++)
        GPIO_PinDirection(i,OUTPUT);

    while(1)
    {

        for(i=LED1;i<=LED4;i++)
            GPIO_PinWrite(i,HIGH);
        DELAY_ms(500);

        for(i=LED1;i<=LED4;i++)
            GPIO_PinWrite(i,LOW);
        DELAY_ms(500);

        for(i=LED1;i<=LED4;i++)
            GPIO_PinWrite(i,HIGH);
        DELAY_ms(500);

        for(i=LED1;i<=LED4;i++)
            GPIO_PinWrite(i,LOW);
        DELAY_ms(500);

        for(i=LED1;i<=LED4;i++)
        {
            GPIO_PinWrite(i,HIGH);
            DELAY_ms(200);
            GPIO_PinWrite(i,LOW);
            DELAY_ms(100);
        }

        for(i=LED4;i>=LED1;i--)
        {
            GPIO_PinWrite(i,HIGH);
            DELAY_ms(200);
            GPIO_PinWrite(i,LOW);
            DELAY_ms(100);
        }
    }
}


void switch_Test(void)
{
    GPIO_PinDirection(LED1,OUTPUT);
    GPIO_PinDirection(LED2,OUTPUT);
    GPIO_PinDirection(LED3,OUTPUT);
    GPIO_PinDirection(SWITCH1,INPUT);
    GPIO_PinDirection(SWITCH2,INPUT);
    GPIO_PinDirection(SWITCH3,INPUT);
    UART0_TxString("\n\n\n\rPress the switches and observe the output on Leds");

    while(1)
    {
        GPIO_PinWrite(LED1,GPIO_PinRead(SWITCH1));
        GPIO_PinWrite(LED2,GPIO_PinRead(SWITCH2));   
        GPIO_PinWrite(LED3,GPIO_PinRead(SWITCH3));            
    }
}


void gpio_Test(void)
{
    uint32_t i;
    uint8_t pins[] = {
    P0_0,P0_1,P0_2,P0_31,P0_3,P0_4,P0_5,P0_6,P0_7,P0_8, P0_9,P0_10,P0_11,P0_12,P0_23,P0_13,
    P0_16,P0_17,P0_18,P0_19,P0_20,P0_21,P0_22,P0_25,P0_28,P0_29,P0_30,  
    P1_16,P1_17,P1_18,P1_19,P1_20,P1_21,P1_22,P1_23,P1_24,P1_25,P1_26,P1_27,P1_28,P1_29,P1_30,P1_31,  
    P_NC        
    };    

    UART0_Printf("\n\r\n\rConnect Leds to all the available pins and observe the status of Leds ");

    for(i=0;pins[i]!=P_NC;i++)
    {
       GPIO_PinDirection(pins[i],OUTPUT);
       GPIO_PinWrite(pins[i],LOW);
    }
    while(1)
        for(i=0;pins[i]!=P_NC;i++)
        {
            GPIO_PinDirection(pins[i],OUTPUT);
            GPIO_PinWrite(pins[i],HIGH);
            DELAY_ms(100);
            GPIO_PinWrite(pins[i],LOW);
            DELAY_ms(100);
        }

}

void lcd_Test(void)
{
    char ch;
    UART0_Printf("Lcd 4-bit Connections\n\r"
            "RS-->P1_16\n\r" 
            "RW-->P1_17\n\r"
            "EN-->P1_18\n\r" 
            "D04-D7 --> P1_20-P1-23\n\r"
            "Press K after doing the connections");
    do
    {
        ch = UART0_RxChar();
    }while((ch!='K') && (ch!='k'));

    LCD_SetUp(P1_16,P1_17,P1_18,P_NC,P_NC,P_NC,P_NC,P1_20,P1_21,P1_22,P1_23);
    LCD_Init(2,16);
    LCD_DisplayString("Explore ARM7\nLPC2148..."); 

    while(1);
}



void adc_Test(void)
{
    ADC_Init();

    while(1)
    {
        UART0_Printf("\n\rAD0.1(P0_28) value= %4d",ADC_GetAdcValue(AD0_1));
    }            
}


void rtc_Test(void)
{
    rtc_t rtc;
    uint8_t old_Seconds = 0xff;

    RTC_Init();
    rtc.hour = 10; //  10:40:20 am
    rtc.min =  40;
    rtc.sec =  0;

    rtc.date = 1; //1st Jan 2016
    rtc.month = 1;
    rtc.year = 2016;
    rtc.weekDay = 5; // Friday: 5th day of week considering monday as first day.

    RTC_SetDateTime(&rtc);  //  10:40:20 am, 1st Jan 2016


    /* Display the Time and Date continuously */
    while(1)
    {
        RTC_GetDateTime(&rtc);
        if(old_Seconds!=rtc.sec)
        {
            UART0_Printf("\n\rtime:%2d:%2d:%2d  Date:%2d/%2d/%4d",(uint16_t)rtc.hour,(uint16_t)rtc.min,(uint16_t)rtc.sec,(uint16_t)rtc.date,(uint16_t)rtc.month,(uint16_t)rtc.year);
            old_Seconds = rtc.sec;
        }
    }            
}


void pwm_Test(void)
{
    int i;
    PWM_Init(255);     /* Initialize the PWM module and the Cycle time(Ton+Toff) is set to 255(similar to arduino) */
    PWM_Start(PWM_2|PWM_4|PWM_6); 

    UART0_Printf("\n\r\n\rConnect the Leds on P0_7,P0_8,P0_9 and observe the fading");

    while(1)
    {

        for(i=0;i<255;i++) /* Increase the Brightness of the Leds */
        {
            PWM_SetDutyCycle(PWM_2,i);
            PWM_SetDutyCycle(PWM_4,i);
            PWM_SetDutyCycle(PWM_6,i);
            DELAY_ms(5);
        }

        for(i=255;i>0;i--) /* Decrease the Brightness of the Leds */
        {
            PWM_SetDutyCycle(PWM_2,i);
            PWM_SetDutyCycle(PWM_4,i);
            PWM_SetDutyCycle(PWM_6,i);
            DELAY_ms(5);
        }
    }            
}    


