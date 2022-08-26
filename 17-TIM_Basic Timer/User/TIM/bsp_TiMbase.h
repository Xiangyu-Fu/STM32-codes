#ifndef __BSP_TIMBASE_H
#define __BSP_TIMBASE_H

#include "stm32f10x.h"

#define BASIC_TIM6

#ifndef BASIC_TIM6
#define BASIC_TIM									TIM6
#define BASIC_TIM_APBxClock_FUN 	RCC_APB1PeriphClockCmd
#define BASIC_TIM_CLK RCC_				APB1Periph_TIM6
#define BASIC_TIM_IRQ 						TIM6_IRQn
#define BASIC_TIM_IRQHandler 			TIM6_IRQHandler

#else
#define BASIC_TIM 								TIM7
#define BASIC_TIM_APBxClock_FUN 	RCC_APB1PeriphClockCmd
#define BASIC_TIM_CLK 						RCC_APB1Periph_TIM7
#define BASIC_TIM_IRQ 						TIM7_IRQn
#define BASIC_TIM_IRQHandler 			TIM7_IRQHandler

#endif


void BASIC_TIM_Init(void);

#endif
