#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue;

// ADC GPIO Initialisation Function
static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	ADC_GPIO_APBxClock_FUN(ADC_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = ADC_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
}

// ADC Operating Mode Configuration
static void ADCx_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_APBxClock_FUN(ADC_CLK, ENABLE);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;

	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	
	ADC_Init(ADCx, &ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL, 1, ADC_SampleTime_55Cycles5);
	
	ADC_ITConfig(ADCx, ADC_IT_EOC, ENABLE);
	
	ADC_Cmd(ADCx, ENABLE);
	
	ADC_ResetCalibration(ADCx);
	
	while(ADC_GetResetCalibrationStatus(ADCx));
	
	ADC_StartCalibration(ADCx);
	
	while(ADC_GetCalibrationStatus(ADCx));
	
	ADC_SoftwareStartConvCmd(ADCx, ENABLE);
}


static void ADC_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* 嵌套向量中断控制器组选择 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置USART为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;
  /* 抢断优先级*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* 子优先级 */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* 使能中断 */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* 初始化配置NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

// ADC Initialisation 
void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADCx_Mode_Config();
	ADC_NVIC_Configuration();
}
