#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "bsp_i2c_ee.h"
#include <stdio.h>

#define  EEP_Firstpage      0x00
uint8_t I2c_Buf_Write[256];
uint8_t I2c_Buf_Read[256];

void delay(uint32_t count)
{
	for(;count!=0;count--);
}

uint8_t I2C_Test(void)
{
	u16 i;
	
	EEPROM_INFO("\n\r写入的数据\n\r");
	
	for (i=0; i<=255;i++)
	{
		I2c_Buf_Write[i] = i;
		printf("0x%02X",I2c_Buf_Write[i]);
		if(i%16 == 15)
				printf("\n\r");
	}
	I2C_EE_BufferWrite(I2c_Buf_Write, EEP_Firstpage, 256);
	
	EEPROM_INFO("\n\r写成功\n\r");
	
	EEPROM_INFO("\n\r读出的数据\n\r");
	
	I2C_EE_BufferRead(I2c_Buf_Read, EEP_Firstpage, 256);
	
	for (i=0; i<=255;i++)
	{
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			EEPROM_ERROR("0x%02X ", I2c_Buf_Read[i]);
			EEPROM_ERROR("错误:I2C EEPROM写入与读出的数据不一致\n\r");
			return 0;
		}
		printf("0x%02X ", I2c_Buf_Read[i]);
    if(i%16 == 15)    
        printf("\n\r");
	}
	EEPROM_INFO("I2C(AT24C02)读写测试成功\n\r");
	return 1;
}

int main()
{
  // initialise the mode of USART as 115200 8-N-1
	USART_Config();
	
	// LED ENABLE
	LED_GPIO_Config(LED_G_GPIO_PIN);
	LED_GPIO_Config(LED_R_GPIO_PIN);
	// LED_GPIO_Config(LED_B_GPIO_PIN);
	
	// Initialise the I2C
	I2C_EE_Init();
	
	if(I2C_Test() == 1)
	{
		LED_G(ON);
		LED_R(OFF);
	}	
	else
	{
	 LED_R(ON);
	 LED_G(OFF);
	}
	
	 while (1)
  {      
  }



#if 0
	char ch = 1;
	          
	// initialise the mode of USART as 115200 8-N-1
	USART_Config();
	
	// LED ENABLE
	LED_GPIO_Config(LED_G_GPIO_PIN);
	LED_GPIO_Config(LED_R_GPIO_PIN);
	LED_GPIO_Config(LED_B_GPIO_PIN);
	
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
