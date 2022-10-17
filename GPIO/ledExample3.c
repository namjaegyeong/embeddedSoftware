#include "lpc17xx_gpio.h"

#define LED_NUM     8

void Delay(long d_t)
{
	long k;
	for(k=0; k<=d_t; k++);
}

int main (void) 
{
	uint32_t sw = 0;
	SystemInit();


	GPIO_SetDir(1, 0xB0000000, 1);         
	GPIO_SetDir(2, 0x0000007C, 1);         
	GPIO_SetDir(2, 0x00000400, 0);			

	GPIO_ClearValue(1, 0xB0000000);
	GPIO_ClearValue(2, 0x0000047C);

 	while(1)
	{
		sw = (GPIO_ReadValue(2) & 0x00000400);
		if(sw == 0x00000000)
		{
			GPIO_SetValue(1, 0xB0000000);
			GPIO_SetValue(2, 0x0000007C);
		}
		else{
			GPIO_ClearValue(1, 0xB0000000); 
			GPIO_ClearValue(2, 0x0000007C);		
		}				
	}
}

