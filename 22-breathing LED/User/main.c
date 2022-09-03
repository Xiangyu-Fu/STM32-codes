#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "stdio.h"
#include "bsp_color_led.h"

void delay(uint32_t count)
{
	for(;count!=0;count--);
}


int main()
{     
	// initialise the mode of USART as 115200 8-N-1
	USART_Config();

	// initialise the TIM gpio
	COLOR_TIMx_LED_init();


	while (1)
	{
		SetRGBColor(0x8080ff);
		delay(0xFFFFF);

		SetRGBColor(0x80ff80);
		delay(0xFFFFF);

		SetRGBColor(0xff8080);
		delay(0xFFFFF);
	}
	
	 
}
