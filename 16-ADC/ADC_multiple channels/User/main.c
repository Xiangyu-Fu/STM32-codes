#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "stdio.h"

extern __IO uint16_t ADC_ConvertedValue[NOFCHANNEL];

float ADC_ConvertedValueLocal[5];

void delay(uint32_t count)
{
	for(;count!=0;count--);
}

int main()
{
	USART_Config();
	
	ADCx_Init();
			
	Usart_SendString(DEBUG_USARTx, "ADC Multiple Channels Interrupt Reading Experiment\n");
	
	while(1)
	{
		ADC_ConvertedValueLocal[0] = (float) ADC_ConvertedValue[0]/4096*3.3;
		ADC_ConvertedValueLocal[1] = (float) ADC_ConvertedValue[1]/4096*3.3;
		ADC_ConvertedValueLocal[2] = (float) ADC_ConvertedValue[2]/4096*3.3;
		ADC_ConvertedValueLocal[3] = (float) ADC_ConvertedValue[3]/4096*3.3;
		ADC_ConvertedValueLocal[4] = (float) ADC_ConvertedValue[4]/4096*3.3;
		
		printf("\r\n CH1 Value = %f V \r\n", ADC_ConvertedValueLocal[0]);
		printf("\r\n CH2 Value = %f V \r\n", ADC_ConvertedValueLocal[1]);
		printf("\r\n CH3 Value = %f V \r\n", ADC_ConvertedValueLocal[2]);
		printf("\r\n CH4 Value = %f V \r\n", ADC_ConvertedValueLocal[3]);
		printf("\r\n CH5 Value = %f V \r\n", ADC_ConvertedValueLocal[4]);
		
		printf("\r\n\r\n");
	
		delay(0xffffee);
	}
	
}
