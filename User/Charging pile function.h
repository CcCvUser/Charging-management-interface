#ifndef Charging pile function_H
#define Charging pile function_H
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
extern u8 sec[17];
extern u8 min[17];
void menu2(void);
void menu1(void);
void menu3(void);
void ttotc(void);
void csd(void);
void tdttdito(void);
void ckcl(void);
void cpapap(void);
#endif
