#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_rccclkconfig.h"


#define GPIOB_ODR_ADDR		(GPIOB_BASE+0x0C)
#define PBout(n) 					*(unsigned int*)((GPIOB_ODR_ADDR & 0xF0000000) + 0x02000000 + ((GPIOB_ODR_ADDR & 0x00FFFFFF)<<5) + (n<<2))

#define GPIOB_IDR_ADDR		(GPIOA_BASE+0x08)
#define PAin(n) 					*(unsigned int*)((GPIOB_IDR_ADDR & 0xF0000000) + 0x02000000 + ((GPIOB_IDR_ADDR & 0x00FFFFFF)<<5) + (n<<2))


#define GPIOC_IDR_ADDR		(GPIOC_BASE+0x08)
#define PCin(n) 					*(unsigned int*)((GPIOC_IDR_ADDR & 0xF0000000) + 0x02000000 + ((GPIOC_IDR_ADDR & 0x00FFFFFF)<<5) + (n<<2))


void delay(uint32_t count)
{
	for(;count!=0;count--);
}

int main()
{
	//HSE_SetSysClk(RCC_PLLMul_9);
	// LED ENABLE
	LED_GPIO_Config(LED_G_GPIO_PIN);				// PIN0
	LED_GPIO_Config(LED_R_GPIO_PIN);				// PIN5		
	//LED_GPIO_Config(LED_B_GPIO_PIN);  		  // PIN1
	
	// GPIO CONFIGURATION
	KEY1_GPIO_Config();
	KEY2_GPIO_Config();
	
#if 0 
	while(1)
	{
		PBout(0) = 1;
		PBout(1) = 1;
		PBout(5) = 1;
		delay(DELAY_TIME);
		PBout(0) = 1;
		PBout(1) = 1;
		PBout(5) = 0;
		delay(DELAY_TIME);
		PBout(0) = 1;
		PBout(1) = 0;
		PBout(5) = 1;
		delay(DELAY_TIME);
		PBout(0) = 0;
		PBout(1) = 1;
		PBout(5) = 1;
		delay(DELAY_TIME);
		PBout(0) = 1;
		PBout(1) = 0;
		PBout(5) = 0;
		delay(DELAY_TIME);
		PBout(0) = 0;
		PBout(1) = 1;
		PBout(5) = 0;
		delay(DELAY_TIME);
		PBout(0) = 0;
		PBout(1) = 0;
		PBout(5) = 1;
		delay(DELAY_TIME);
		
	}

#elif 1	
	//MAIN LOOP
	while (1)
	{
		if(PAin(0)==KEY_ON)
		{
			while(PAin(0)==KEY_ON);
			LED_G_TOGGLE;
		}
		if(PCin(13)==KEY_ON)
		{
			while(PCin(13)==KEY_ON);
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
