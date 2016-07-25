#include <lpc214x.h>
#include "stdutils.h"
#include "systemInit.h"

void delay_ms(unsigned int ms)
{
    unsigned int i,j;
    for(i=0;i<ms;i++)
        for(j=0;j<50000;j++);
} 


#define SBIT_CNTEN     0 
#define SBIT_PWMEN     3

#define SBIT_PWMMR0R   1

#define SBIT_LEN0      0
#define SBIT_LEN1      1
#define SBIT_LEN2      2
#define SBIT_LEN3      3
#define SBIT_LEN4      4

#define SBIT_PWMENA1   9
#define SBIT_PWMENA2   10
#define SBIT_PWMENA3   11
#define SBIT_PWMENA4   12

#define PWM1_PINSEL           0 //P0_0 (0-1   Bits of PINSEL0)
#define PWM2_PINSEL          14 //P0_7 (14-15 Bits of PINSEL0)
#define PWM3_PINSEL           2 //P0_2 (2-3   Bits of PINSEL0)
#define PWM4_PINSEL          16 //P0_8 (16-17 Bits of PINSEL0)

int main(void)
{
    int dutyCycle;
    SystemInit();
    
    /* Cofigure pins(P0_0, P0_7, P0_1, P0_8) for PWM mode. */
    PINSEL0 = (2<<PWM1_PINSEL) | (2<<PWM2_PINSEL) | (2<<PWM3_PINSEL) | (2<<PWM4_PINSEL);  

    PWMPR  =  0x00;              /* No Prescalar */
    PWMMCR = (1<<SBIT_PWMMR0R);  /*Reset on PWMMR0, reset TC if it matches MR0 */

    PWMMR0 = 100;                /* set PWM cycle(Ton+Toff)=100) */
    PWMMR1 = 50;                 /* Set 50% Duty Cycle for all four channels */
    PWMMR2 = 50;
    PWMMR3 = 50;
    PWMMR4 = 50;
	PWMTC  = 0x00;
    /* Trigger the latch Enable Bits to load the new Match Values */
    PWMLER = (1<<SBIT_LEN0) | (1<<SBIT_LEN1) | (1<<SBIT_LEN2) | (1<<SBIT_LEN3) | (1<<SBIT_LEN4); 

    /* Enable the PWM output pins for PWM_1-PWM_4(P2_0 - P2_3) */
    PWMPCR = (1<<SBIT_PWMENA1) | (1<<SBIT_PWMENA2) | (1<<SBIT_PWMENA3) | (1<<SBIT_PWMENA4);

	    /* Enable Counters,PWM module */ 
    PWMTCR = (1<<SBIT_CNTEN) | (1<<SBIT_PWMEN);

    while(1)
    {
        for(dutyCycle=0; dutyCycle<100; dutyCycle++)
        {
            PWMMR1 = dutyCycle;  /* Increase the dutyCycle from 0-100 */
            PWMMR2 = dutyCycle;
            PWMMR3 = dutyCycle;
            PWMMR4 = dutyCycle;
            /* Trigger the latch Enable Bits to load the new Match Values */
            PWMLER = (1<<SBIT_LEN0) | (1<<SBIT_LEN1) | (1<<SBIT_LEN2) | (1<<SBIT_LEN3) | (1<<SBIT_LEN4); 
            delay_ms(5);
        }

        for(dutyCycle=100; dutyCycle>0; dutyCycle--)
        {
            PWMMR1 = dutyCycle;  /* Decrease the dutyCycle from 100-0 */
            PWMMR2 = dutyCycle;
            PWMMR3 = dutyCycle;
            PWMMR4 = dutyCycle;
            /* Trigger the latch Enable Bits to load the new Match Values */
            PWMLER = (1<<SBIT_LEN0) | (1<<SBIT_LEN1) | (1<<SBIT_LEN2) | (1<<SBIT_LEN3) | (1<<SBIT_LEN4); 
            delay_ms(5);
        }
    }
} 
