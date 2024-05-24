/**
  ******************************************************************************
  * @file    SysTick/SysTick_Example/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    13-April-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "delay.h"
#include "LED.h"
#include "CH455I2C.H"
#include "key.h"
#include "USART3.h"
#include "MPU6050.h"
unsigned char k=0;
extern u8 key;
/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup SysTick_Example
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

void SysTick_Handler(void)
{
  /*  static unsigned int cnt = 0;
    
    cnt++;
    
    if(cnt == 500)
    {
        cnt = 0;
        
        LED4_REVERSE;
    }*/
    key=KeyScan();
		/*if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		    for(c=1;c<17;c++)
		{
		    if(flag[c]==1)
				{
					sec[c]++;
					if(sec[c]>59)
					{
						sec[c]=0;
						min[c]++;
					}
				}
				else
				{
					sec[c]=0;
					min[c]=0;
				}
			}*/
    TimingDelay_Decrement();
//}
}
extern u8 ch455_key;

void EXTI9_5_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
    {        
        EXTI_ClearITPendingBit(EXTI_Line5);
        
        ch455_key = CH455_Read();
    }
}
const u8 BCD_decode_tab2[0x10] = { 0X3F, 0X06, 0X5B, 0X4F, 0X66, 0X6D, 0X7D, 0X07, 0X7F, 0X6F, 
									 0X77, 0X7C, 0X58, 0X5E, 0X79, 0X71 };//BCD

extern u8 flag1[17];
extern u8 i,time;
u8 c;
u8 sec[17]={0};
u8 min[17]={0};
void TIM2_IRQHandler(void)
{
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		    for(c=1;c<17;c++)
		{
		    if(flag1[c]==1)
				{
					sec[c]++;
					if(sec[c]>59)
					{
						sec[c]=0;
						min[c]++;
					}
				}
				else
				{
					sec[c]=0;
					min[c]=0;
				}
			}
		if(time)
		{
				CH455_Write(CH455_DIG3 | BCD_decode_tab2[sec[i] % 10]);
        CH455_Write(CH455_DIG2 | BCD_decode_tab2[sec[i]/ 10]);
        CH455_Write(CH455_DIG1 | BCD_decode_tab2[min[i] % 10]);
        CH455_Write(CH455_DIG0 | BCD_decode_tab2[min[i]/ 10]);
		}
		  
	}
	
}
void USART6_IRQHandler(void)
{
    if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)                //  若接收数据寄存器满
	{
		USART_ClearITPendingBit(USART6, USART_IT_RXNE);
        
        Uart6.Rxbuf[Uart6.RXlenth] = USART_ReceiveData(USART6);
        
        if (Uart6.RXlenth == 0 && Uart6.Rxbuf[0] != 0x55)
        {
            Uart6.RXlenth = 0;
            return;
        }
        if (Uart6.RXlenth == 1 && Uart6.Rxbuf[1] != 0x53)
        {
            Uart6.RXlenth = 0;
            return;
        }
        
        
        Uart6.RXlenth++;
        
        if(Uart6.RXlenth == 11)
        {
            memcpy(databuf, &Uart6.Rxbuf[0], 20);
            
            display_flag = 1;
            Uart6.RXlenth = 0;
        }
    }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
