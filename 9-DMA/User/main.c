#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "stdio.h"
#include "bsp_dma.h"


static void Delay(uint32_t count)
{
	for(;count!=0;count--);
}

int main()
{	          
	uint16_t i;  
	extern uint8_t SendBuff[SENDBUFF_SIZE];
	
	// LED ENABLE
	LED_GPIO_Config(LED_G_GPIO_PIN);
	LED_GPIO_Config(LED_R_GPIO_PIN);
	LED_GPIO_Config(LED_B_GPIO_PIN);

#if 1
  /* 初始化USART */
  USART_Config(); 

  /* 配置使用DMA模式 */
  USARTx_DMA_Config();
  
  //printf("\r\n USART1 DMA TX 测试 \r\n");
  
  /*填充将要发送的数据*/
  for(i=0;i<SENDBUFF_SIZE;i++)
  {
    SendBuff[i]	 = '1';
    
  }

  /*为演示DMA持续运行而CPU还能处理其它事情，持续使用DMA发送数据，量非常大，
  *长时间运行可能会导致电脑端串口调试助手会卡死，鼠标乱飞的情况，
  *或把DMA配置中的循环模式改为单次模式*/		
  
  /* USART1 向 DMA发出TX请求 */
  USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);

  /* 此时CPU是空闲的，可以干其他的事情 */  
  //例如同时控制LED
  while(1)
  {
    LED_G_TOGGLE;
    Delay(0xFFFFF);
  }


#elif 0	
	// show the tips message
	Show_Message();
	
	while(1)
	{
		// get char
		ch = getchar();
		printf("接收到的字符：%c \n",ch);
		
		switch(ch)
		{
		case '1':
			LED_R(ON);
			LED_G(OFF);
			LED_B(OFF);
			break;
		case '2':
			LED_R(OFF);
			LED_G(ON);
			LED_B(OFF);
			break;
		case '3':
			LED_R(OFF);
			LED_G(OFF);
			LED_B(ON);
			break;
		case '4':
			LED_R(ON);
			LED_G(ON);
			LED_B(OFF);
			break;
		case '5':
			LED_R(ON);
			LED_G(OFF);
			LED_B(ON);
			break;
		case '6':
			LED_R(OFF);
			LED_G(ON);
			LED_B(ON);
			break;
		case '7':
			LED_R(ON);
			LED_G(ON);
			LED_B(ON);
			break;
		case '8':
			LED_R(OFF);
			LED_G(OFF);
			LED_B(OFF);
			break;
		default:
			Show_Message();
			break;
		}
		
	}
	 
#elif 0	
	// LED ENABLE
	LED_GPIO_Config(LED_G_GPIO_PIN);
	LED_GPIO_Config(LED_R_GPIO_PIN);
	LED_GPIO_Config(LED_B_GPIO_PIN);
	
	// GPIO CONFIGURATION
	KEY1_GPIO_Config();
	KEY2_GPIO_Config();

	//MAIN LOOP
	while (1)
	{
		if(Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN)==KEY_ON)
		{
			LED_G_TOGGLE;
		}
		if(Key_Scan(KEY2_GPIO_PORT, KEY2_GPIO_PIN)==KEY_ON)
		{
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
