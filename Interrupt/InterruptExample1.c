#include "lpc17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_libcfg_default.h"   
#include "lpc17xx_pinsel.h"

uint32_t pos;

void Delay(long d_t)
{
	long k;
	for (k=0; k<d_t; k++);
}

void EINT0_IRQHandler(void)
{                   
  	LPC_SC->EXTINT = 0x01; 
	pos = 0x04;
}
 
int main (void) 
{
   	PINSEL_CFG_Type PinCfg; //Import PINSEL_CFG structure
   	SystemInit(); //system initialization
   	GPIO_SetDir(1, 0xB0000000, 1);
   	GPIO_SetDir(2, 0x0000007C, 1); //Set 2,3,4,5,6 of GPIO2 as output    
 
   	GPIO_ClearValue(1, 0xB0000000); //Set 28,29,31 of GPIO1 off : LED 1,2,3 off
   	GPIO_ClearValue(2, 0x0000007C); //Set 2,3,4,5,6 of GPIO2 off : LED 4,5,6,7,8 off
   
   /* External interrupt parameter initialization */
	
   	LPC_SC->EXTINT = 0x0;
   	LPC_SC->EXTMODE = 0x0;
   	LPC_SC->EXTPOLAR = 0x0;     

  	LPC_SC->EXTMODE = 0x1;	  // 에지 트리거 인터럽트 설정	
  	LPC_SC->EXTPOLAR = 0x0;	  // 하강 에지 트리거 인터럽트 설정  

	PinCfg.Funcnum = 1;           // 포트 2의 10번 EINT0을 동작 설정
	PinCfg.OpenDrain = 0;         // 오픈 드레인 사용하지 않음
	PinCfg.Pinmode = 0;            // Pull-Up
	PinCfg.Pinnum = 10;            // 10 핀 설정
	PinCfg.Portnum = 2;            // 포트 2 설정
   
   	PINSEL_ConfigPin(&PinCfg); 
	 
   	NVIC_EnableIRQ(EINT0_IRQn);  // EINT0 활성화
	 
   while(1)
  {   
		GPIO_SetValue(2, pos);
		Delay(600000);
  }
}