#ifndef __BSP_WWDG_H
#define __BSP_WWDG_H

# include "stm32f10x.h"

#define WWDG_CNT	0X7F
void WWDG_IRQHandler(void);
void WWDG_Feed(void);
void WWDG_CONFIG(uint8_t prescaler, uint8_t window, uint32_t prv);

#endif