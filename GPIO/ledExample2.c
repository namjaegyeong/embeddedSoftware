#include "lpc17xx_gpio.h"

#define LED_NUM     8

const unsigned long led_mask[] = { 1<<28, 1<<29, 1UL<<31, 1<<2, 1<<3, 1<<4, 1<<5, 1<<6 };

void Delay(long d_t)
{
	long k;
	for(k=0; k<=d_t; k++);
}

int main (void) 
{
	int num = -1;
	int dir =  1;

	SystemInit();

	GPIO_SetDir(1, 0xB0000000, 1); 
	GPIO_SetDir(2, 0x0000007C, 1);          

	GPIO_ClearValue(1, 0xB0000000);
	GPIO_ClearValue(2, 0x0000007C);

	while(1)
	{
		//TODO
	}
}

