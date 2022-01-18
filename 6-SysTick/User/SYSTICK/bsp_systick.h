#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

#include "stm32f10x.h"


void SysTick_Delay_us(uint32_t us);
void SysTick_Delay_ms(uint32_t ms);
void TimingDelay_Decrement(void);
void Int_Delay_ms(__IO uint32_t nTime);

#endif /*__BSP_SYSTICK_H*/

