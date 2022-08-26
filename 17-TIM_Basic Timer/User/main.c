#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_TiMbase.h"

volatile u32 time = 0;

void delay(uint32_t count)
{
	uint16_t i,j;
	for(i=0;i<count;i++)
		{for(j=0;j<count;j++);}
}

int main()
{
	// LED ENABLE
	LED_GPIO_Config(LED_G_GPIO_PIN);
	LED_GPIO_Config(LED_R_GPIO_PIN);
	LED_GPIO_Config(LED_B_GPIO_PIN);
	LED_G(ON);
	
	BASIC_TIM_Init();
	
	while(1)
	{
		if(time == 1000)
		{
			time = 0;
			LED_G_TOGGLE;
		}
	}
}
