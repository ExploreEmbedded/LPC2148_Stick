#include <lpc214x.h>
#include "stdutils.h"
#include "systemInit.h"
#include "pwm.h"
#include "delay.h"

#define CYCLE_TIME 255

/* start the main program */
int main() 
{
    int dutyCycle;
    SystemInit();             /* Clock and PLL configuration */ 
    PWM_Init(CYCLE_TIME);     /* Initialize the PWM module and the Cycle time(Ton+Toff) is set to 255(similar to arduino)*/
    PWM_Start(PWM_1|PWM_2|PWM_3|PWM_4); /* Enable PWM output on PWM_1-PWM_4 (P0_0, P0_7, P0_1, P0_8) */

    while(1)
    {
        for(dutyCycle=0;dutyCycle<CYCLE_TIME;dutyCycle++) /* Increase the Brightness of the Leds */
        {
            PWM_SetDutyCycle(PWM_1,dutyCycle);  //P0_0
            PWM_SetDutyCycle(PWM_2,dutyCycle);  //P0_7
            PWM_SetDutyCycle(PWM_3,dutyCycle);  //P0_1
            PWM_SetDutyCycle(PWM_4,dutyCycle);  //P0_8
            DELAY_ms(5);
        }

        for(dutyCycle=CYCLE_TIME;dutyCycle>0;dutyCycle--) /* Decrease the Brightness of the Leds */
        {
            PWM_SetDutyCycle(PWM_1,dutyCycle);  //P0_0
            PWM_SetDutyCycle(PWM_2,dutyCycle);  //P0_7
            PWM_SetDutyCycle(PWM_3,dutyCycle);  //P0_1
            PWM_SetDutyCycle(PWM_4,dutyCycle);  //P0_8
            DELAY_ms(5);
        }
    }                              
}
