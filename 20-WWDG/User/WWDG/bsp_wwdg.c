#include "bsp_wwdg.h"


static void WWDG_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

// WWDG_CONFIG
/*
 * @brief: This function is used to configure the WWDG.
 * @param: uint8_t wr: the window value, range from 0x7F to 0x40.
 * @param: uint8_t tr: the timeout value, range from 0x7F~0x40.
 * @param: uint8_t prv: the prescaler value, the value can be 
 *      @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
 *      @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
 *      @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
 *      @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
 */
void WWDG_CONFIG(uint8_t tr, uint8_t wr, uint32_t prv)
{
    // 开启WWDG时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
    
    // WWDG初始化
    WWDG_SetPrescaler(prv);
    WWDG_SetWindowValue(wr);
    WWDG_SetCounter(tr);
    
    // WWDG使能
    WWDG_Enable(WWDG_CNT);

    // WWDG中断使能
    WWDG_ClearFlag();

    // 配置中断优先级
    WWDG_NVIC_Config();

    // WWDG中断使能
    WWDG_EnableIT();

}


void WWDG_Feed(void)
{
    WWDG_SetCounter(WWDG_CNT);
}
