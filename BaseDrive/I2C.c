#include "I2C.h"
#include "delay.h"

/**********************************************************************************************************
函数名称：I2C_GPIO_Configuration
输入参数：无
输出参数：无
函数返回：无
引脚定义：
//SCL	PF1
//SDA	PF0
**********************************************************************************************************/
void I2C_GPIO_Configuration(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);   //使能GPIOB时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_4;    //LED对应引脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;           //通用输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;          //输出推挽
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //100MHz
//    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //无上拉或下拉
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOG, &GPIO_InitStructure);                  //初始化 GPIO
   
    I2C_Stop();
}

/**********************************************************************************************************
函数名称：配置SDA为输入
输入参数：无
输出参数：无
函数返回：无
引脚定义：
//SDA	PF0
**********************************************************************************************************/
void I2C_SDA_Input(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
}

/**********************************************************************************************************
函数名称：配置SDA为输出
输入参数：无
输出参数：无
函数返回：无
引脚定义：
//SDA	PF0
**********************************************************************************************************/
void I2C_SDA_Output(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);
}

/**********************************************************************************************************
函数名称：I2C_delay
输入参数：无
输出参数：无
函数返回：无
**********************************************************************************************************/
void I2C_delay(void)
{
    delay_us(10);
}

/**********************************************************************************************************
函数名称：I2C_Start
输入参数：无
输出参数：无
函数返回：无
**********************************************************************************************************/
void I2C_Start(void)
{
    SDA_H;                    											//	拉高数据线
    SCL_H;                    											//	拉高时钟线
    I2C_delay();                 										//	延时
    
    SDA_L;                   	 										//	产生下降沿
    I2C_delay();                 										//	延时
    
    SCL_L;                    											//	拉低时钟线
    I2C_delay();                 										//	延时
}


/**********************************************************************************************************
函数名称：I2C_Stop
输入参数：无
输出参数：无
函数返回：无
**********************************************************************************************************/
void I2C_Stop(void)
{
    SCL_H;                    											//	拉高时钟线
    SDA_L;                    											//	拉低数据线
    I2C_delay();                 										//	延时
    
    SDA_H;                   							 				//	产生上升沿
    I2C_delay();                 										//	延时
}


/**********************************************************************************************************
函数名称：I2C_SendACK
输入参数：无
输出参数：无
函数返回：无
**********************************************************************************************************/
void I2C_SendACK(unsigned char ack)
{
    if (ack == 1)
	{
		SDA_H;
	}
    else
	{
        SDA_L;                  										//	写应答信号
	}	
    
    SCL_H;                    											//	拉高时钟线
    I2C_delay();                 										//	延时
    
    SCL_L;                    											//	拉低时钟线
    I2C_delay();                 										//	延时
}


/**********************************************************************************************************
函数名称：I2C_Start
输入参数：无
输出参数：无
函数返回：接收到的ACK
**********************************************************************************************************/
void I2C_ReceiveACK(void)
{
    unsigned char errcnt = 20;
	
    I2C_SDA_Input();
    
    I2C_delay();                 										//	延时
    
    SCL_H;                    											//	拉高时钟线
    I2C_delay();                 										//	延时
    
	while (SDA_READ())
	{
        errcnt--;
        
        if (!errcnt)
        {
            I2C_Stop();
        }
	}
    
    SCL_L;                    											//	拉低时钟线
    I2C_SDA_Output();
    I2C_delay();                 										//	延时
}


/**********************************************************************************************************
函数名称：I2C_SendByte
输入参数：发送的1字节数据
输出参数：无
函数返回：无
**********************************************************************************************************/
void I2C_SendByte(unsigned char dat)
{
    unsigned char i;
	
    for (i = 0; i < 8; i++)     										//	8位计数器
    {
        if (dat & 0x80)
		{
            SDA_H;               										//	送数据口
		}
        else
		{
            SDA_L;
		}

        dat <<= 1;              										//	移出数据的最高位
        
        SCL_H;                											//	拉高时钟线
        I2C_delay();             										//	延时
        
        SCL_L;                											//	拉低时钟线
        I2C_delay();             										//	延时
    }
    I2C_ReceiveACK();
}

/**********************************************************************************************************
函数名称：I2C_Start
输入参数：无
输出参数：无
函数返回：接收到的数据
**********************************************************************************************************/
unsigned char I2C_ReceiveByte(void)
{
    unsigned char i;
    unsigned char dat = 0;
    
	I2C_SDA_Input();
	
    for (i = 0; i < 8; i++)     										//	8位计数器
    {
        dat <<= 1;
        
        SCL_H;                											//	拉高时钟线
        I2C_delay();             										//	延时
        
        
		if (SDA_READ())
		{
			dat |= 1;             										//	读数据
		}
        
        SCL_L;                											//	拉低时钟线
        I2C_delay();             										//	延时
    }
    I2C_SDA_Output();
	
    return dat;
}

