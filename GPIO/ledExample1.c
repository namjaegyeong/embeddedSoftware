#include "lpc17xx_gpio.h"


void Delay(unsigned long d_t)
{
	long k;
	for(k=0; k<d_t; k++);
}


int main(void)
{
	SystemInit();

	GPIO_SetDir(1, 0xB0000000, 1);
	GPIO_SetDir(2, 0x0000007C, 1);

	GPIO_ClearValue(1, 0xB0000000);
	GPIO_ClearValue(2, 0x0000007C);

	while(1)
	{
		GPIO_SetValue(1, 0xB0000000);
		GPIO_SetValue(2, 0x0000007C);
		Delay(5000000);
		GPIO_ClearValue(1, 0xB0000000); 
		GPIO_ClearValue(2, 0x0000007C);
		Delay(5000000);
	}
}
	
