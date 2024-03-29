// board support package �弶֧�ְ�
#include "bsp_led.h"

void LED_GPIO_Config(uint32_t pin)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = pin;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

void LED_RGB_Init(void)
{
LED_GPIO_Config(LED_R_GPIO_PIN);
LED_GPIO_Config(LED_G_GPIO_PIN);
LED_GPIO_Config(LED_B_GPIO_PIN);

LED_R(OFF);
LED_G(OFF);
LED_B(OFF);	
}


