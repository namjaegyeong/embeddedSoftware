#include "lpc17xx_gpio.h"
#include "lpc17xx_mcpwm.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"

//MCPWM 채널 설정 구조체
MCPWM_CHANNEL_CFG_Type PWMSetup;
PINSEL_CFG_Type PWMPin[2];
uint32_t PWMValue = 0;
uint32_t PeriodValue = 300;
uint8_t UpDownFlag = 0;

void Delay(long d_t)
{
   long k;
   for(k=0; k<=d_t; k++);
}

int main(void)
{
   SystemInit ();
   
   GPIO_SetDir(1, 0x80000000, 1);
   GPIO_SetDir(2, 0x0000007C, 1);
   
   GPIO_ClearValue(1, 0x80000000);
   GPIO_ClearValue(2, 0x0000007C);
   
   
   //포트 1의 28번 핀 설정
   PWMPin[0].Portnum = 1;
   PWMPin[0].Pinnum = 28;
   PWMPin[0].Funcnum = 1;
   PWMPin[0].Pinmode = 0;
   PWMPin[0].OpenDrain = 0;

      //포트 1의 29번 핀 설정
   PWMPin[1].Portnum = 1;
   PWMPin[1].Pinnum = 29;
   PWMPin[1].Funcnum = 1;
   PWMPin[1].Pinmode = 0;
   PWMPin[1].OpenDrain = 0;

   PINSEL_ConfigPin(&PWMPin[0]);
   PINSEL_ConfigPin(&PWMPin[1]);
      
   MCPWM_Init(LPC_MCPWM);   //MCPWM 초기화

   PWMSetup.channelType = MCPWM_CHANNEL_EDGE_MODE;       //Edge-Aligned 된 PWM 파형을 사용
   PWMSetup.channelPolarity = MCPWM_CHANNEL_PASSIVE_LO;       //Passive 상태에서 Low신호를 출력하도록 설정
   PWMSetup.channelDeadtimeEnable = DISABLE;       //PWM 데드타임 카운터 사용하지 않음   
   PWMSetup.channelDeadtimeValue = 0;       //PWM 데드타임 카운터 시간을 0으로 설정   
   PWMSetup.channelUpdateEnable = ENABLE;       //PWM 펄스 폭 값을 계속해서 변경
   PWMSetup.channelTimercounterValue = 0;       //MCPWM 타이머/카운터 값을 0으로 초기화
   PWMSetup.channelPeriodValue = PeriodValue;       //MCPWM의 파형 주기 설정 값
   PWMSetup.channelPulsewidthValue = PWMValue;       //MCPWM의 파형 펄스 폭 설정 값
   
   MCPWM_ConfigChannel(LPC_MCPWM, 2, &PWMSetup);       //MCPWM의 2번 채널에 PWMSetup 구조체의 설정
   
   MCPWM_Start(LPC_MCPWM, DISABLE, DISABLE, ENABLE);    //MCPWM의 동작을 시작

   while(1)
   {
      if(UpDownFlag == 0)
         PWMValue++;
      else
         PWMValue--;
      
      Delay(100000);
      PWMSetup.channelPulsewidthValue = PWMValue;
      
      MCPWM_WriteToShadow(LPC_MCPWM, 2, &PWMSetup);
      
      if(PWMValue == PeriodValue)
         UpDownFlag = 1;
      else if(PWMValue == 0)
         UpDownFlag = 0;
   }
}