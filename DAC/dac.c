#include "lpc17xx_dac.h"
#include "lpc17xx_uart.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "debug_frmwrk.h"

int main(void)
{
      PINSEL_CFG_Type PinCfg;
      uint32_t time;
      float rate = 0;
   
      SystemInit();
   
      PinCfg.Funcnum = 2;
      PinCfg.OpenDrain = 0;
      PinCfg.Pinmode = 0;
      PinCfg.Pinnum = 26;
      PinCfg.Portnum = 0;
      PINSEL_ConfigPin (&PinCfg);
   
      DAC_Init(LPC_DAC);

      while (1)
      {
         for(time = 1; time < 0x3FF; time++)
         {   //DAC 값 업데이트
            DAC_UpdateValue ( LPC_DAC,(uint32_t)(time*rate));
         }
      }
      rate += 0.001;

      if(rate >= 1)
      {
         rate = 0;
      }
}
