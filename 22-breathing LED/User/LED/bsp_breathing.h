#ifndef __BSP_BREATHING_H
#define __BSP_BREATHING_H

#include "stm32f10x.h"

#define RED_LIGHT 1
#define GREEN_LIGHT 2
#define BLUE_LIGHT 3

#define LIGHT_COLOR RED_LIGHT

#if LIGHT_COLOR == RED_LIGHT
#define BRE_TIMx                    TIM3
#define BRE_TIMx_CLK                RCC_APB1Periph_TIM3
#define BRE_TIM_GPIO_APBxClock_FUN  RCC_APB2PeriphClockCmd
#define BRE_TIM_GPIO_CLK           (RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO)

// the pin of the red light
#define BRE_GPIO_REMAP_FUN()        GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE)
#define BRE_TIM_LED_PIN             GPIO_Pin_5
#define BRE_TIM_LED_PORT            GPIOB

#define BRE_TIM_OCxInit             TIM_OC2Init // the channel of the red light. 1~4
#define BRE_TIM_OCxPreloadConfig    TIM_OC2PreloadConfig
#define BRE_CCRx                    CCR2

#define BRE_TIMx_IRQn               TIM3_IRQn            // the interrupt of the timer
#define BRE_TIMx_IRQHandler         TIM3_IRQHandler

#elif LIGHT_COLOR == GREEN_LIGHT
#define BRE_TIMx                    TIM3
#define BRE_TIMx_CLK                RCC_APB1Periph_TIM3
#define BRE_TIM_GPIO_APBxClock_FUN  RCC_APB2PeriphClockCmd
#define BRE_TIM_GPIO_CLK           (RCC_APB2Periph_GPIOB)

// the pin of the green light
#define BRE_TIM_LED_PIN             GPIO_Pin_0
#define BRE_TIM_LED_PORT            GPIOB
#define BRE_TIM_OCxInit             TIM_OC3Init // the channel of the green light. 1~4
#define BRE_TIM_OCxPreloadConfig    TIM_OC3PreloadConfig
#define BRE_CCRx                    DMA_CCR3_CIRC

#define BRE_TIMx_IRQn               TIM3_IRQn            // the interrupt of the timer
#define BRE_TIMx_IRQHandler         TIM3_IRQHandler

#elif LIGHT_COLOR == BLUE_LIGHT
#define BRE_TIMx                    TIM3
#define BRE_TIMx_CLK                RCC_APB1Periph_TIM3
#define BRE_TIM_GPIO_APBxClock_FUN  RCC_APB2PeriphClockCmd
#define BRE_TIM_GPIO_CLK           (RCC_APB2Periph_GPIOB)

#define BRE_TIM_LED_PIN             GPIO_Pin_1
#define BRE_TIM_LED_PORT            GPIOB
#define BRE_TIM_OCxInit             TIM_OC4Init // the channel of the blue light. 1~4
#define BRE_TIM_OCxPreloadConfig    TIM_OC4PreloadConfig
#define BRE_CCRx                    CCR4

#define BRE_TIMx_IRQn               TIM3_IRQn            // the interrupt of the timer
#define BRE_TIMx_IRQHandler         TIM3_IRQHandler

#endif

#endif