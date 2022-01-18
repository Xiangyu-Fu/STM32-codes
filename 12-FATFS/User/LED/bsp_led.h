#ifndef __BSP_LED_H  // ������Ƶ����⣿
#define __BSP_LED_H

#include "stm32f10x.h"

/*Ϊ����߳���Ŀ���ִ�У���Ӳ����صĶ�����ɺ�*/
#define LED_G_GPIO_PIN		GPIO_Pin_0
#define LED_R_GPIO_PIN		GPIO_Pin_5
#define LED_B_GPIO_PIN		GPIO_Pin_1

#define LED_GPIO_PORT			GPIOB
#define LED_GPIO_CLK			RCC_APB2Periph_GPIOB
#define DELAY_TIME				((uint32_t)0xFFF)

#define 	ON 		1
#define 	OFF 	0

#define		LED_G(x) 				if(x) \
																GPIO_ResetBits(LED_GPIO_PORT, LED_G_GPIO_PIN); \
													else 	GPIO_SetBits(LED_GPIO_PORT, LED_G_GPIO_PIN);
#define		LED_R(x) 				if(x) \
																GPIO_ResetBits(LED_GPIO_PORT, LED_R_GPIO_PIN); \
													else 	GPIO_SetBits(LED_GPIO_PORT, LED_R_GPIO_PIN);
#define		LED_B(x) 				if(x) \
																GPIO_ResetBits(LED_GPIO_PORT, LED_B_GPIO_PIN); \
													else 	GPIO_SetBits(LED_GPIO_PORT, LED_B_GPIO_PIN);
						
#define LED_G_TOGGLE 	{LED_GPIO_PORT->ODR ^= LED_G_GPIO_PIN;}
#define LED_R_TOGGLE 	{LED_GPIO_PORT->ODR ^= LED_R_GPIO_PIN;}


void LED_GPIO_Config(uint32_t pin);
void LED_RGB_Init(void);
void LED_RED(void);
void LED_GREEN(void);
void LED_BLUE(void);

//��
#define LED_RED  \
					LED_R(ON);\
					LED_G(OFF)\
					LED_B(OFF)

//��
#define LED_GREEN		\
					LED_R(OFF);\
					LED_G(ON)\
					LED_B(OFF)

//��
#define LED_BLUE	\
					LED_R(OFF);\
					LED_G(OFF)\
					LED_B(ON)

					
//��(��+��)					
#define LED_YELLOW	\
					LED_R(ON);\
					LED_G(ON)\
					LED_B(OFF)
//��(��+��)
#define LED_PURPLE	\
					LED_R(ON);\
					LED_G(OFF)\
					LED_B(ON)

//��(��+��)
#define LED_CYAN \
					LED_R(OFF);\
					LED_G(ON)\
					LED_B(ON)
					
//��(��+��+��)
#define LED_WHITE	\
					LED_R(ON);\
					LED_G(ON)\
					LED_B(ON)
					
//��(ȫ���ر�)
#define LED_RGBOFF	\
					LED_R(OFF);\
					LED_G(OFF)\
					LED_B(OFF)



#endif /*__BSP_LED_H*/
