#include "bsp_rccclkconfig.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x)
{
	ErrorStatus HSEstatus;
	
	// ��ʼ��RCC�Ĵ���
	RCC_DeInit();

	// ʹ��HSE
	RCC_HSEConfig(RCC_HSE_ON);
	
	HSEstatus = RCC_WaitForHSEStartUp();
	
	if(HSEstatus == SUCCESS)
	{
		// ʹ��Ԥȡֵ
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		
		// ���õȴ�����״̬
		FLASH_SetLatency(FLASH_Latency_2);
		
		// �������������ϵķ�Ƶ����
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		// ����PLLCLK = HSE * RCC_PLLMul_x
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
		
		// ʹ��PLL
		RCC_PLLCmd(ENABLE);
		
		// �ȴ�PLL�ȶ�
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		
		// ����PLL��Ϊϵͳʱ��
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		// �ȴ�ʱ���������
		while(RCC_GetSYSCLKSource() != 0x08);
		
		
		
	}
	else
	{
		/* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
	}
}
