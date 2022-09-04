## TIM advanced timer
输出比较结构体 `TIM_OCInitTypeDef`

```c
    // 互补输出通道空闲电平极性配置
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
    TIM_OC1Init(ADVANCE_TIM, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(ADVANCE_TIM, TIM_OCPreload_Enable);
```

TIM 重载寄存器ARR --> Review the TIM

## DEBUG
From last night, I stuck in a bug that I found that I cannot open the breathing led, even I checked all of the code but I couldn't find anything. But compared with the example code, I found that the clock of TIM was not open. I use the same clock function on the two periperals. So,  next time, please notice that you must open the clock for all peripheral correctly.