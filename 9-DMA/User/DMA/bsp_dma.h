#ifndef __BSP_DMA_H 
                         
#define __BSP_DMA_H                          

#include "stm32f10x.h"

//DEFINITIONS OF DMA
// 串口对应的DMA 请求通道
#define USART_TX_DMA_CHANNEL DMA1_Channel4
#define USART_DR_ADDRESS (USART1_BASE+0x04) // Data Register
#define SENDBUFF_SIZE 100

void USARTx_DMA_Config(void);

#endif /*__BSP_DMA_H*/
 









 