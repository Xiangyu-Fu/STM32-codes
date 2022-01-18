#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "stdio.h"

void delay(uint32_t count)
{
	for(;count!=0;count--);
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
	
	while(1)
	{
		// get char
		ch = getchar();
		printf("接收到的字符：%c \n",ch);
		
		switch(ch)
		{
		case '1':
			LED_R(ON);
			LED_G(OFF);
			LED_B(OFF);
			break;
		case '2':
			LED_R(OFF);
			LED_G(ON);
			LED_B(OFF);
			break;
		case '3':
			LED_R(OFF);
			LED_G(OFF);
			LED_B(ON);
			break;
		case '4':
			LED_R(ON);
			LED_G(ON);
			LED_B(OFF);
			break;
		case '5':
			LED_R(ON);
			LED_G(OFF);
			LED_B(ON);
			break;
		case '6':
			LED_R(OFF);
			LED_G(ON);
			LED_B(ON);
			break;
		case '7':
			LED_R(ON);
			LED_G(ON);
			LED_B(ON);
			break;
		case '8':
			LED_R(OFF);
			LED_G(OFF);
			LED_B(OFF);
			break;
		default:
			Show_Message();
			break;
		}
		
	}
	 
#if 0	
	// LED ENABLE
	LED_GPIO_Config(LED_G_GPIO_PIN);
	LED_GPIO_Config(LED_R_GPIO_PIN);
	LED_GPIO_Config(LED_B_GPIO_PIN);
	
	// GPIO CONFIGURATION
	KEY1_GPIO_Config();
	KEY2_GPIO_Config();

	//MAIN LOOP
	while (1)
	{
		if(Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN)==KEY_ON)
		{
			LED_G_TOGGLE;
		}
		if(Key_Scan(KEY2_GPIO_PORT, KEY2_GPIO_PIN)==KEY_ON)
		{
			LED_R_TOGGLE;
		}
	}
	
#elif 0
	while(1)
	{
		//GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
		LED_G(OFF);
		LED_B(OFF);
		LED_R(ON);
		delay(DELAY_TIME);
		
		LED_G(OFF);
		LED_B(ON);
		LED_R(OFF);
		delay(DELAY_TIME);
		
		LED_G(ON);
		LED_B(OFF);
		LED_R(ON);
		delay(DELAY_TIME);
		
		LED_G(OFF);
		LED_B(ON);
		LED_R(ON);
		delay(DELAY_TIME);
		
		LED_G(ON);
		LED_B(ON);
		LED_R(OFF);
		delay(DELAY_TIME);
		
		LED_G(OFF);
		LED_B(OFF);
		LED_R(ON);
		delay(DELAY_TIME);
		
		LED_G(OFF);
		LED_B(ON);
		LED_R(OFF);
		delay(DELAY_TIME);
		//LED_G(OFF);
		//GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
		//delay(0xFFFFF);
	}
#endif
}
