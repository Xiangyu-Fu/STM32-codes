#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue[NOFCHANNEL];

// ADC GPIO Initialisation Function
static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	ADC_GPIO_APBxClock_FUN(ADC_GPIO_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = ADC_PIN1
															|ADC_PIN2
															|ADC_PIN3
															|ADC_PIN4
															|ADC_PIN5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	
	GPIO_Init(ADC_PORT, &GPIO_InitStructure);
}

// ADC Operating Mode Configuration
static void ADCx_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	// Clocks
	ADC_APBxClock_FUN(ADC_CLK, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	/*------------DMA MODE CONFIGURATION-----------*/
	DMA_DeInit(ADC_DMA_CHANNEL);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = 	(u32)(&(ADCx->DR)); 
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32)ADC_ConvertedValue;         
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;         
	DMA_InitStructure.DMA_BufferSize = NOFCHANNEL;            
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStructure);
	
	DMA_Cmd (ADC_DMA_CHANNEL,ENABLE);
	
	
	/*------------ADC MODE CONFIGURATION-----------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	
	ADC_InitStructure.ADC_NbrOfChannel = NOFCHANNEL;	
	ADC_Init(ADCx, &ADC_InitStructure);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	
	// Configure the conversion order and sampling time of the ADC channels
	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL1, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL2, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL3, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL4, 4, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADCx, ADC_CHANNEL5, 5, ADC_SampleTime_55Cycles5);
	
	//ADC_ITConfig(ADCx, ADC_IT_EOC, ENABLE);	
	ADC_DMACmd(ADCx, ENABLE);
	
	// start ADC and convert
	ADC_Cmd(ADCx, ENABLE);

	// Initialise Calibration Register	
	ADC_ResetCalibration(ADCx);
	while(ADC_GetResetCalibrationStatus(ADCx));
	
	// Start ADC Calibration
	ADC_StartCalibration(ADCx);	
	while(ADC_GetCalibrationStatus(ADCx));
	
	// Since no external triggering is used, software is used to trigger the ADC conversion.
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
