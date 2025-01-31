/**-------------------------------------------------------------------------------------------
** Created by:          qinyx
** Last modified Date:  2014-02-28
** Last Version:        V1.00
** Descriptions:        STM32F407嵌入式实验箱
**	  Gpio配置文件
**
**-------------------------------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "TIME.h"

/**********************************************************************************************************
函数名称：定时器初始化函数
输入参数：无
输出参数：无
定时器：TIM2
**********************************************************************************************************/
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure one bit for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);


    /* Timer2中断*/
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /* 基础设置*/
    TIM_TimeBaseStructure.TIM_Period = 10000-1;							//	计数值
    TIM_TimeBaseStructure.TIM_Prescaler = 8400-1;						//	预分频
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 		//	向上计数

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    /*使能预装载*/
    TIM_ARRPreloadConfig(TIM2, ENABLE);

    /*预先清除所有中断位*/
    TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

    /* 溢出配置中断*/
    TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);

    /* 允许TIM2开始计数 */
    TIM_Cmd(TIM2, ENABLE);
}

