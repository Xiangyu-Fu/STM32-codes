## TIM advanced timer
输出比较结构体 `TIM_OCInitTypeDef`

```c
    // 互补输出通道空闲电平极性配置
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC1Init(ADVANCE_TIM, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);
```