#ifndef __BSP_ADC_H
#define __BSP_ADC_H

#include "stm32f10x.h"

// ADC number selection
#define ADC_APBxClock_FUN 			RCC_APB2PeriphClockCmd
#define ADCx 										ADC1
#define ADC_CLK 								RCC_APB2Periph_ADC1

// ADC GPIO Macros Definitions
#define ADC_GPIO_APBxClock_FUN 	RCC_APB2PeriphClockCmd
#define ADC_GPIO_CLK 						RCC_APB2Periph_GPIOC
#define ADC_PORT 								GPIOC

// numbers of convert channels
#define NOFCHANNEL								5

#define ADC_PIN1 								GPIO_Pin_0
#define ADC_CHANNEL1						ADC_Channel_10

#define ADC_PIN2 								GPIO_Pin_1
#define ADC_CHANNEL2						ADC_Channel_11

#define ADC_PIN3 								GPIO_Pin_2
#define ADC_CHANNEL3						ADC_Channel_12

#define ADC_PIN4 								GPIO_Pin_3
#define ADC_CHANNEL4						ADC_Channel_13

#define ADC_PIN5 								GPIO_Pin_4
#define ADC_CHANNEL5						ADC_Channel_14

// ADC1 correspond to DMA1 channel 1, ADC correspond to DMA2 channel 5, ADC2 has no DMA functions
#define ADC_DMA_CHANNEL					DMA1_Channel1

// ADC Interruption Macro Definitions
#define ADC_IRQ 								ADC1_2_IRQn
#define ADC_IRQHandler 					ADC1_2_IRQHandler

void ADCx_Init(void);

#endif
