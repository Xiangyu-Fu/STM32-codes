#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "stdio.h"

extern __IO uint16_t ADC_ConvertedValue;

float ADC_ConvertedValueLocal;

void delay(uint32_t count)
{
	for(;count!=0;count--);
}

int main()
{
	USART_Config();
	
	ADCx_Init();
			
	Usart_SendString(DEBUG_USARTx, "ADC single Channel Interrupt Reading Experiment\n");
	
	while(1)
	{
		ADC_ConvertedValueLocal = (float) ADC_ConvertedValue/4096*3.3;
		
		printf("\r\n The current AD value = 0x%04X \r\n", ADC_ConvertedValue);
		printf("\r\n The current AD value = %f V \r\n", ADC_ConvertedValueLocal);
		printf("\r\n\r\n");
	
		delay(0xffffee);
	}
	
}
