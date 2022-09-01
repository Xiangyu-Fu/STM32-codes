#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_key.h"

void delay(uint32_t count)
{
	for(;count!=0;count--);
}

int main()
{
	// LED ENABLE
	LED_GPIO_Config(LED_G_GPIO_PIN);
	LED_GPIO_Config(LED_R_GPIO_PIN);
	//LED_GPIO_Config(LED_B_GPIO_PIN);
	
	// GPIO CONFIGURATION
	// KEY1_GPIO_Config();
	// KEY2_GPIO_Config();
	
	//MAIN LOOP
#if 1
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
