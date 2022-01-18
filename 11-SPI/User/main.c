#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "bsp_spi_flash.h"
#include <stdio.h>


/* 获取缓冲区的长度 */
#define 	countof(a)      (sizeof(a) / sizeof(*(a)))
#define  	BufferSize 			(countof(Tx_Buffer) - 1) 


uint8_t Tx_Buffer[] = "这是一个SPI FLASH测试实验 \r\n";
uint8_t Rx_Buffer[BufferSize];

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress

typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;
__IO TestStatus TransferStatus = FAILED;

void Delay(uint32_t count);
TestStatus Buffercmp(uint8_t* pBuffer1,uint8_t* pBuffer2, uint16_t BufferLength);

int main()
{
	// initialise the mode of USART as 115200 8-N-1
	USART_Config();
	
	// LED ENABLE
	LED_RGB_Init();
	LED_BLUE();
	
	printf("\r \n 这是一个 8MByte 串行 FLASH（W25Q64）实验\r \n");
	
	// Initialise the 8M serial FLASH
	SPI_FLASH_Init(); 
	
	// Get the Device ID
	DeviceID = SPI_FLASH_ReadDeviceID();
	Delay(200);
	
	// Get the SPI FLASH ID
	FlashID = SPI_FLASH_ReadID();
	printf("\r\n FlashID is 0x%X, Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	
	// check the SPI FLASH ID
	if (FlashID == sFLASH_ID)
	{
		printf("\r\n Serial Flash W25Q64 has been detected!\r\n");
		
		// Erase the specific sector in Flash
		SPI_FLASH_SectorErase(FLASH_SectorToErase);
		
		// Write specific data in flash
		SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);
		printf("\r\n Data writed in flash is %s \r\n", Tx_Buffer);
		
		SPI_FLASH_BufferRead(Rx_Buffer, FLASH_WriteAddress, BufferSize);
		printf("\r\n Data read from flash is %s \r\n", Tx_Buffer);
		
		TransferStatus = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
		
		if(TransferStatus != FAILED)
		{
			LED_GREEN();
			printf("\r\n 8M Serial flash (W25Q64) test successfully! \r\n");		
		}
		else
		{
			LED_RED();
			printf("\r\n 8M Serial flash (W25Q64) test failed! \r\n");
		}
	}
	
	else
	{
		LED_RED();
		printf("\r\n W25Q64 ID cannot be found!\r\n");
	}
	
#if 0 //USART - LED
	// show the tips message
	Show_Message();
	char ch = 1;	
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
void Delay(uint32_t count)
{
	for(;count!=0;count--);
}

TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }
  return PASSED;
}
