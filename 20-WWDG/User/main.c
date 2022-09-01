#include "stm32f10x.h" 
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"
#include "stdio.h"
#include "bsp_wwdg.h"

void delay(uint32_t count)
{
	for(;count!=0;count--);
}

void send_message(char *message)
{
	while(*message)
	{
		printf("%c",*message);
	}
}

int main()
{
	uint8_t wwdg_tr, wwdg_wr;
	          
	// initialise the mode of USART as 115200 8-N-1
	USART_Config();
	
	// LED ENABLE
	LEDS_Init();
	
	LED_B(ON);
	delay(0xFFFFF);

	WWDG_CONFIG(0x7F, 0x5F, WWDG_Prescaler_8);

	// we initialise the window value to 0x5F, and the counter value to 0x7F
	// Where the CFR is the whachdog configuration register
	wwdg_wr = WWDG->CFR & 0x7F;
	
	// Besides, we also need to rememeber some other register. 
	// CFR is the whachdog configuration register, which aims to costomise the up-window value.
	// CR is the whachdog control register, which is the decresing encounter.
	// RLR is the reload register.
	// TR is the timeout register.
	// WR is the window register, which customized by the user.


	while(1){
		LED_B(OFF); // Blue LED blink for one time

		// Here we can add some code which need to be monitored.
		wwdg_tr = WWDG->CR & 0x7F;

		// if the counter value is equal to the window value, we can reset the counter value to 0x7F.
		if (wwdg_tr < wwdg_wr){
			WWDG_Feed(); // if commit this line, the red led will light up.
		}
	}

}
