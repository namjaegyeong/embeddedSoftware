#include "lpc17xx.h"
#include "lpc17xx_gpio.h"
#include "lpc17xx_timer.h"
#include "lpc17xx_libcfg_default.h"

uint8_t g_ulFlags = 0;

TIM_TIMERCFG_Type TIM_ConfigStruct; //Timer 설정 구조체
TIM_MATCHCFG_Type TIM_MatchConfigStruct ; //Timer 일치 동작 구조체

void Delay(long d_t)
{
   long k;
   for(k=0; k<=d_t; k++);
}

void TIMER0_IRQHandler(void)
{
   TIM_ClearIntPending(LPC_TIM0,0); //Timer0 인터럽트 클리어
   
   g_ulFlags++;
   
   if(g_ulFlags == 2)
      g_ulFlags = 0;
}

int main(void)
{
   SystemInit();
   
   GPIO_SetDir(1, 0xB0000000, 1);
   GPIO_SetDir(2, 0x0000007C, 1);

   GPIO_ClearValue(1, 0xB0000000);
   GPIO_ClearValue(2, 0x0000007C);

   TIM_ConfigStruct.PrescaleOption = TIM_PRESCALE_USVAL; //마이크로 초 단위로 타이머 clock을 환산
   TIM_ConfigStruct.PrescaleValue = 100; //1 clock 당 카운트 시간은 100㎲ 설정

   TIM_MatchConfigStruct.MatchChannel = 0; //타이머0을 사용하도록 설정
   TIM_MatchConfigStruct.IntOnMatch = ENABLE; //타이머 일치 동작시 인터럽트가 발생
   TIM_MatchConfigStruct.ResetOnMatch = ENABLE; //타이머 일치 동작시 타이머의 값을 리셋
   TIM_MatchConfigStruct.StopOnMatch = DISABLE; //타이머 일치 동작을 주기적으로 발생
   TIM_MatchConfigStruct.ExtMatchOutputType=TIM_EXTMATCH_NOTHING; //타이머의 외부 출력핀은 사용하지 않음
   TIM_MatchConfigStruct.MatchValue = 5000; //0.5초 간격으로 타이머 일치 동작이 발생 5000 * 100㎲ = 500ms

   TIM_Init(LPC_TIM0, TIM_TIMER_MODE,&TIM_ConfigStruct); //타이머/카운터 장치를 초기화 한다.
   TIM_ConfigMatch(LPC_TIM0,&TIM_MatchConfigStruct); //타이머 일치 동작을 설정한다.

   NVIC_EnableIRQ(TIMER0_IRQn); //TIMER0_IRQn 인터럽트 활성화
   TIM_Cmd(LPC_TIM0,ENABLE); //TIM0 동작

   while(1){
      if(g_ulFlags == 0)
      {
         GPIO_SetValue(1, 0xB0000000);
         GPIO_SetValue(2, 0x0000007C);
      }
      else if(g_ulFlags == 1)
      {
         GPIO_ClearValue(1, 0xB0000000);
         GPIO_ClearValue(2, 0x0000007C);
      }
   }
}