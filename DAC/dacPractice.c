#include "lpc17xx_dac.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "debug_frmwrk.h"
#include "lpc17xx_timer.h"

uint8_t g_ulFlags = 0;

TIM_TIMERCFG_Type TIM_ConfigStruct; //Timer 설정 구조체
TIM_MATCHCFG_Type TIM_MatchConfigStruct ; //Timer 일치 동작 구조체

void TIMER0_IRQHandler(void)
{
   TIM_ClearIntPending(LPC_TIM0,0); //Timer0 인터럽트 클리어
   
   g_ulFlags++;
   
   if(g_ulFlags == 5)
      g_ulFlags = 0;
}

int main(void)
{
    PINSEL_CFG_Type PinCfg;
    uint32_t time;
    float rate = 1;

    SystemInit();

    PinCfg.Funcnum = 2;
    PinCfg.OpenDrain = 0;
    PinCfg.Pinmode = 0;
    PinCfg.Pinnum = 26;
    PinCfg.Portnum = 0;
    PINSEL_ConfigPin (&PinCfg);

    DAC_Init(LPC_DAC);

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
      
    while (1)
    {
        if(g_ulFlags == 0)
        {
            for(time = 1; time < 0x0EF; time++)
            {   //DAC 값 업데이트
                DAC_UpdateValue ( LPC_DAC,(uint32_t)(time*rate));
            }
        } else if(g_ulFlags == 1)
        {
            for(time = 1; time < 0x0FF; time++)
            {   //DAC 값 업데이트
                DAC_UpdateValue ( LPC_DAC,(uint32_t)(time*rate));
            }
        } else if(g_ulFlags == 2)
        {
            for(time = 1; time < 0x1FF; time++)
            {   //DAC 값 업데이트
                DAC_UpdateValue ( LPC_DAC,(uint32_t)(time*rate));
            }
        } else if(g_ulFlags == 3)
        {
            for(time = 1; time < 0x2FF; time++)
            {   //DAC 값 업데이트
                DAC_UpdateValue ( LPC_DAC,(uint32_t)(time*rate));
            }
        } else if(g_ulFlags == 4)
        {
            for(time = 1; time < 0x3FF; time++)
            {   //DAC 값 업데이트
                DAC_UpdateValue ( LPC_DAC,(uint32_t)(time*rate));
            }
        }
    }
}
