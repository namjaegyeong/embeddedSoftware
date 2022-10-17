#include "lpc17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_libcfg_default.h"   
#include "lpc17xx_pinsel.h"

uint8_t led;

void Delay(long d_t)
{
	long k;
	for (k=0; k<d_t; k++);
}

void EINT0_IRQHandler(void)
{   				 	
  	LPC_SC->EXTINT = 0x01; 		
	//Todo	         
}

int main(void)
{
	PINSEL_CFG_Type PinCfg;
	SystemInit();
	GPIO_SetDir(1, 0xB0000000, 1);
	GPIO_SetDir(2, 0x0000007C, 1);
	
	GPIO_ClearValue(1, 0xB0000000);
	GPIO_ClearValue(2, 0x0000007C);	
	
  	LPC_SC->EXTINT = 0x0;
  	LPC_SC->EXTMODE = 0x0;
  	LPC_SC->EXTPOLAR = 0x0;	  
						
  	LPC_SC->EXTMODE = 0x1;	
  	LPC_SC->EXTPOLAR = 0x0;	 

	PinCfg.Funcnum = 1;      
	PinCfg.OpenDrain = 0;       
	PinCfg.Pinmode = 0;           
	PinCfg.Pinnum = 10;          
	PinCfg.Portnum = 2;          
	PINSEL_ConfigPin(&PinCfg);

	NVIC_EnableIRQ(EINT0_IRQn); 
	
	while(1){
		//Todo	
	}
}
