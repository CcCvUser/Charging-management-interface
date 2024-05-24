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
�������ƣ�main����
�����������
�����������
�������أ���
**********************************************************************************************************/

int main(void)
{ 
	  SysTick_Init();                     //  ϵͳ�δ�ʱ����ʼ��
	  KEYGpio_Init();                     //  ����IO�ڳ�ʼ��
	  LEDGpio_Init();                     //  ��ʼ��LED
    LCD_Init();                     //  Һ����ʼ��
    SysTick_Handler();
    LCD_Clear(WHITE); 
    init_CH455();                       //  ��ʼ��
	  CH455_Write( CH455_SYSON );	
	  UART3_Configuration();    		//  USART3����
    UART6_Configuration(9600);
		setMp3Dev(UDISK);            		//  U��
    setMp3Vol(30);             		//  ��������
	  TIM2_Configuration();
		menu1();
}

