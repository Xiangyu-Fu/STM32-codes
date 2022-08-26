#include "bsp_TiMbase.h"

static void BASIC_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	 // 开启定时器时钟,即内部时钟CK_INT=72M
   BASIC_TIM_APBxClock_FUN(BASIC_TIM_CLK, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period = 1000;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	
	TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(BASIC_TIM, TIM_FLAG_Update);
	
	TIM_ITConfig(BASIC_TIM, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(BASIC_TIM, ENABLE);
}

static void BASIC_TIM_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	// 设置中断组为0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	// 设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ ;
	// 设置主优先级为0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	// 设置抢占优先级为3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void BASIC_TIM_Init(void)
{
	BASIC_TIM_NVIC_Config();
	BASIC_TIM_Mode_Config();
}
