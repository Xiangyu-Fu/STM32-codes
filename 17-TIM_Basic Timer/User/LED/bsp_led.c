// board support package 
#include "bsp_led.h"

// configure LED 
void LED_GPIO_Config(uint32_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
	
	GPIO_SetBits(LED_GPIO_PORT, pin);
}


