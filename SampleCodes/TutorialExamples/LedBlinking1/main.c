#include <lpc214x.h>

void delay_ms(unsigned int count)
{
  unsigned int j=0,i=0;
  for(j=0;j<count;j++)
  {
    for(i=0;i<3000;i++);
  }
}

/* start the main program */
int main() 
{
    PINSEL2 = 0x000000;  //Configure the P1 Pins for GPIO;
    IODIR1 = 0xffffffff; //Configure the P1 pins as OUTPUT;

  while(1)
    {
       IOSET1 = 0xffffffff;     // Make all the Port pins as high  
         delay_ms(1000);

       IOCLR1 = 0xffffffff;     // Make all the Port pins as low  
         delay_ms(1000);
    }
}
