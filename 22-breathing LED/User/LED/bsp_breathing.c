#include "bsp_breathing.h"

static void ADVANCE_TIM_Mode_Config(void)
{
    ADVANCE_TIM_APBxClock_FUN(ADVANCE_TIM_CLK, ENABLE);

    /* time base configuration */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Period = ADVANCED_TIM_PERIOD;
    TIM_TimeBaseStructure.TIM_Prescaler = ADVANCED_TIM_PSC;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(ADVANCE_TIMx, &TIM_TimeBaseStructure);

    /* output compare configuration */
    TIM_OCInitTypeDef TIM_OCInitStructure;
    // configure the PWM mode to pwm1
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  
    // enable the output
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    // enable the compare output
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    // 
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

    TIM_OC1Init(ADVANCE_TIMx, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(ADVANCE_TIMx, TIM_OCPreload_Enable);
    

}