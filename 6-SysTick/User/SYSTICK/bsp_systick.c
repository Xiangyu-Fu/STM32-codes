#include "bsp_systick.h"

uint32_t TimingDelay;

void SysTick_Delay_us(uint32_t us)
{
	uint32_t i=0;
	
	SysTick_Config(720);
		
	for(;i<us;i++)
	{
		while(!((SysTick->CTRL) & (1<<16)));
	}
	
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_ms(uint32_t ms)
{
	uint32_t i=0;
	
	SysTick_Config(72000);
		
	for(;i < ms;i++)
	{
		while(!((SysTick->CTRL) & (1<<16)));
	}
	
	SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}

void Int_Delay_ms(__IO uint32_t nTime)
{
	// ����Systick��ʱ��
	SysTick_Config(72000);
	
	// ���ö�ʱʱ��
	TimingDelay = nTime;
	
	// �ȴ���ʱ���
	while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{
	// �жϷ��������ú�������
	if(TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}

