#include "stm32f10x.h"

int main(void)
{
	// enable the clock
	RCC_APB2ENR |= (1<<3);
	
	// reset the mode of PB0
	GPIOB_CRL &= ~(0x0F << (4*3));
	
	// configure PB0 to the push/pull output
	GPIOB_CRL |= (1<<4*3);
	
	// configure the output data register
	GPIOB_ODR &= ~(1<<0);
}

void SystemInit(void)
{
	
}