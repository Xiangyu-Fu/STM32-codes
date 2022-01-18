#include "bsp_rccclkconfig.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	ErrorStatus HSEstatus;
	
	// 初始化RCC寄存器
	RCC_DeInit();

	// 使能HSE
	RCC_HSEConfig(RCC_HSE_ON);
	
	HSEstatus = RCC_WaitForHSEStartUp();
	
	if(HSEstatus == SUCCESS)
	{
		// 使能预取值
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		
		// 设置等待两个状态
		FLASH_SetLatency(FLASH_Latency_2);
		
		// 配置三个主线上的分频因子
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		// 配置PLLCLK = HSE * RCC_PLLMul_x
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
		
		// 使能PLL
		RCC_PLLCmd(ENABLE);
		
		// 等待PLL稳定
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		// 设置PLL作为系统时钟
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		// 等待时钟设置完毕
		while(RCC_GetSYSCLKSource() != 0x08);
		
		
		
	}
	else
	{
		/* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
	}
}
