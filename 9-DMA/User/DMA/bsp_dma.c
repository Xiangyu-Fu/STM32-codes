#include "bsp_dma.h"


uint8_t SendBuff[SENDBUFF_SIZE];

void USARTx_DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	
	// enable the clock of DMA
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr = 	USART_DR_ADDRESS;  // 外设地址
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32)SendBuff;         // 存储器地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;           // 传输方向
	DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;            // 设定待传输数据数目
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;	
	DMA_Init(USART_TX_DMA_CHANNEL, &DMA_InitStructure);
	
	DMA_Cmd (USART_TX_DMA_CHANNEL,ENABLE);      
}












