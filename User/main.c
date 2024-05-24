#include "main.h"
#include "delay.h"
#include "LED.h"
#include "KEY.h"
#include "PWM.h"
#include "DCMotor.h"
#include "CH455I2C.H"
#include "lcd.h"
#include "pic1.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx.h"
#include "TIME.h"
#include "mp3.h"
#include "USART3.h"
#include "MPU6050.h"
#include "KEY.h"
#include "stdio.h"
#include "Charging pile function.h"
/**********************************************************************************************************
函数名称：main函数
输入参数：无
输出参数：无
函数返回：无
**********************************************************************************************************/

int main(void)
{ 
	  SysTick_Init();                     //  系统滴答定时器初始化
	  KEYGpio_Init();                     //  按键IO口初始化
	  LEDGpio_Init();                     //  初始化LED
    LCD_Init();                     //  液晶初始化
    SysTick_Handler();
    LCD_Clear(WHITE); 
    init_CH455();                       //  初始化
	  CH455_Write( CH455_SYSON );	
	  UART3_Configuration();    		//  USART3配置
    UART6_Configuration(9600);
		setMp3Dev(UDISK);            		//  U盘
    setMp3Vol(30);             		//  设置音量
	  TIM2_Configuration();
		menu1();
}

