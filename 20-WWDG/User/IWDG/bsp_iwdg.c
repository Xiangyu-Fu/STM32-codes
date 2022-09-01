#include "bsp_iwdg.h"

// Function: bsp_iwdg_init
// Description: Initialize the IWDG
// Input: prv: Prescaler value (0-7)
//        rlv: Reload value (0-0xFFF), Tout = prv/40 * rlv(s)
void IWDG_CONFIG(uint8_t prv, uint16_t rlv)
{
    // 使能预分频寄存器和重装载寄存器的写操作
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    // 设置IWDG预分频值
    IWDG_SetPrescaler(prv);

    // 设置IWDG重装载值
    IWDG_SetReload(rlv);

    // 按照IWDG重装载寄存器的值重装载IWDG计数器
    IWDG_ReloadCounter();

    // 使能IWDG
    IWDG_Enable();
}

void IWDG_Feed(void)
{
    // 按照IWDG重装载寄存器的值重装载IWDG计数器
    IWDG_ReloadCounter();
}