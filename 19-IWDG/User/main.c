#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "stdio.h"
#include "bsp_iwdg.h"

void delay(uint32_t count)
{
	for(;count!=0;count--);
}

void send_message(char *message)
{
	while(*message)
	{
		printf("%c",*message);
	}
}

int main()
{
	char ch = 1;
	          
	// initialise the mode of USART as 115200 8-N-1
	USART_Config();
	
	// LED ENABLE
	LED_GPIO_Config(LED_G_GPIO_PIN);
	LED_GPIO_Config(LED_R_GPIO_PIN);
	LED_GPIO_Config(LED_B_GPIO_PIN);
	
	// show the tips message
	Show_Message();
	
	// check if is the individual watch dog reset
	if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
		// individual watch dog reset and the LED will be on
		LED_R(ON);
		delay(0xFFFFF);
		LED_R(OFF);
		delay(0xFFFFF);
		LED_R(ON);
		// clear the individual watch dog reset flag
		RCC_ClearFlag();

	}
	else
	{
		// not individual watch dog reset and the LED will be off
		LED_B(ON);
	}

	// config the key gpio
	KEY1_GPIO_Config();
	// config the IWDG
	IWDG_CONFIG(IWDG_Prescaler_64,625);

	while (1)
	{
		// here will be the code which need to be monitored

		if(Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON)
		{
			LED_R(OFF);
			IWDG_Feed();
			LED_G(ON);
		}
	}

}
