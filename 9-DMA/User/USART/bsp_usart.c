#include "bsp_usart.h"

static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
	
	// �����ж����ȼ�����
	// NVIC_Configuration();
	
	// ʹ�ܴ��ڽ����ж�
	// USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
	
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USARTx, ENABLE);	    
}


void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)       // ����������USART�ϵ�ֵ
{
	 USART_SendData(pUSARTx, ch);
	 
	 while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void Usart_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t data)
{
	uint8_t temp_h, temp_l;
	
	temp_h = (data&0xff00) >> 8;
	temp_l = data&0xff;
	
	USART_SendData(pUSARTx, temp_h);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(pUSARTx, temp_l);
	while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
}

void Usart_SendString(USART_TypeDef *pUSARTx, char *str)     
{
	 unsigned int k=0;
	 
	 do{
			Usart_SendByte(pUSARTx, *(str+k));
			k++;
	 }while (*(str+k) != '\0'); 
	 
	 
	 while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET){}
}

// redirect the printf and scanf function
int fputc(int ch, FILE *f)
{
	/* transmit a byte to USART*/
	USART_SendData(DEBUG_USARTx, (uint8_t) ch);
	
	/* Awaiting for transmitting */
	while(USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);
	
	return (ch);
}

// redirect the scanf function to USART, after redirecting you can use scanf() and getchar() etc.
int fgetc(FILE *f)
{
	while(USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE)  == RESET); // ��ȡ�Ĵ����ǿ�
	
	return (int)USART_ReceiveData(DEBUG_USARTx);
}

void Show_Message(void)
{
	printf("\r\n ����һ��ͨ������ͨ��ָ�����RGB�Ĳʵ�ʵ��\n");
	printf("ʹ��USART����Ϊ�� %d 8-n-1\n", DEBUG_USART_BAUDRATE);
	printf("������ӵ�ָ������RGB�ʵƵ���ɫ�� ָ���Ӧ���£�\n");
	printf("ָ�� ----- �ʵ���ɫ\n");
	printf("	 1 ----- ��\n");
	printf("	 2 ----- ��\n");
	printf("	 3 ----- ��\n");
	printf("	 4 ----- ��\n");
	printf("	 5 ----- ��\n");
	printf("	 6 ----- ��\n");
	printf("	 7 ----- ��\n");
	printf("	 8 ----- ��\n");
}
