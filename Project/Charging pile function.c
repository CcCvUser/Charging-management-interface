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



extern unsigned char k;
unsigned char Int_flag = 0;                                             
extern const u8 BCD_decode_tab2[0x10];  //数码管时间显示数组
u8 ch455_key;  //CH455的按键键值
u8 flag1[17]={0}; //代表1~16个充电桩的通断状态，1代表通电，0代表断电
u8 key;  //按键键值
u8 i,time;  //i代表按键键值转换而来的按键号（1~16），即各个充电口号；time是时间显示标识符，当time为1时，时间显示数码管打开显示充电时间，当time为0时，时间显示数码管熄灭
u8 showH[2],showL[2];      
float a;  //行变量
u8 b;	    //列变量



void ttotc()    //The status of the charging pile(各充电桩状态)
{         u8 d=0;
	        for(b=0;b<3;b=b+2) //b=0;b<3;b=b+2
				{

         		    for( a=0;a<9;a=a+1.2) // a=0;a<9;a=a+1.2      
									{ 										 
										d=d++;
										if(!flag1[d])LCD_DrawPicture(150*b, a*80, 150*(b+1), (a+1)*80, (u8*)gImage_456);
										else LCD_DrawPicture(150*b, a*80, 150*(b+1), (a+1)*80, (u8*)gImage_123);
										
								}
			}
}

void csd()   //Charging slogan display(充电口号显示)
{
			LCD_ShowString(75+0*150, 81+0*96, "P1",BLACK, WHITE);
			LCD_ShowString(75+0*150, 81+1*96, "P2",BLACK, WHITE);
			LCD_ShowString(75+0*150, 81+2*96, "P3",BLACK, WHITE);           
			LCD_ShowString(75+0*150, 81+3*96, "P4",BLACK, WHITE);
			LCD_ShowString(75+0*150, 81+4*96, "P5",BLACK, WHITE);
			LCD_ShowString(75+0*150, 81+5*96, "P6",BLACK, WHITE);
			LCD_ShowString(75+0*150, 81+6*96, "P7",BLACK, WHITE);
			LCD_ShowString(75+0*150, 81+7*96, "P8",BLACK, WHITE);
		
			LCD_ShowString(75+2*150, 81+0*96, "P9",BLACK, WHITE);
			LCD_ShowString(75+2*150, 81+1*96, "P10",BLACK, WHITE);
			LCD_ShowString(75+2*150, 81+2*96, "P11",BLACK, WHITE);
			LCD_ShowString(75+2*150, 81+3*96, "P12",BLACK, WHITE);
			LCD_ShowString(75+2*150, 81+4*96, "P13",BLACK, WHITE);
			LCD_ShowString(75+2*150, 81+5*96, "P14",BLACK, WHITE);
			LCD_ShowString(75+2*150, 81+6*96, "P15",BLACK, WHITE);
			LCD_ShowString(75+2*150, 81+7*96, "P16",BLACK, WHITE);
}

void tdttdito()   //The digital tube time display is turned off(数码管时间显示关闭)
{
			CH455_Write(CH455_DIG3 | 0X00);
      CH455_Write(CH455_DIG2 | 0X00);
      CH455_Write(CH455_DIG1 | 0X00);
      CH455_Write(CH455_DIG0 | 0X00);
}  

void ckcl()   //CNC keyboard conversion logo(数控键盘转换标识)
{
	    
		  i = ch455_key & 0x3f;//按键值
        if( i<=7 )
        {      
				
           i=i-3;           
        }else if( 12<=i & i<=15 )
        {              
           i=i-7;
        }else if( 20<=i & i<=23 )
        {           
           i=i-11;
        }else
        {
           i=i-15;
        }
}

void cpapap()   //Control power-on and power-off and play voice(控制通断电并播放语音)
{
	        if( i<9 )
        {  
					 if(!flag1[i])
			  {  
					 LCD_DrawPicture(0, (i-1)*96, 150, i*96-16, (u8*)gImage_123);
					switch(i)
					{
						case 1:mp3Play1();					
						break;
						case 2:mp3Play2();
						break;
						case 3:mp3Play3();
						break;
						case 4:mp3Play4();
						break;
						case 5:mp3Play5();
						break;
						case 6:mp3Play6();
						break;
						case 7:mp3Play7();
						break;
						case 8:mp3Play8();
						break;

					}
				}        
					 else
					 {
						LCD_DrawPicture(0, (i-1)*96, 150, i*96-16, (u8*)gImage_456);            
					 }
           flag1[i]=1-flag1[i];
     
        }else
        {
					if(!flag1[i])
					 {
					 LCD_DrawPicture(300, (i-9)*96, 450, (i-9)*96+80, (u8*)gImage_123);
						switch(i)
					{

						case 9:mp3Play9();
						break;
						case 10:mp3Play10();
						break;
						case 11:mp3Play11();
						break;
						case 12:mp3Play12();
						break;
						case 13:mp3Play13();
						break;
						case 14:mp3Play14();
						break;
						case 15:mp3Play15();
						break;
						case 16:mp3Play16();
						break;	
					}
					 }
					 else
					 {
          LCD_DrawPicture(300, (i-9)*96, 450, (i-9)*96+80, (u8*)gImage_456);          
					 }
					flag1[i]=1-flag1[i];       
        }
}

/*****************
     菜单函数
*****************/

void menu1()
{ 
	    LCD_Clear(WHITE); 
	    LCD_ShowString(100, 100, "1.按下S2查看各充电口情况",BLACK, WHITE);
      LCD_ShowString(100, 120, "2.按下S3管理各充电口",BLACK, WHITE);
	while(1)
	{   
		  key=KeyScan(); 
			if(key==2)
			{
				menu2();
			}
			if(key==3)
			{
				menu3();
			}
	}
	
}
void menu2()
{ 
	    LCD_Clear(WHITE);
		  LCD_ShowString(151, 400, "点击充电桩查看充电",BLACK, WHITE);
	    LCD_ShowString(210, 420, "时间",BLACK, WHITE);
      ttotc();
			while(1)
			{
			key=KeyScan();
			csd();
		  #ifdef USE_CH455_KEY
		 ch455_key = 0xff;
		 while( ch455_key == 0xff )
{
	   key=KeyScan();
	
	   if(key==1)
				{ 
					time=0;
          tdttdito();
					menu1();
				}
	   if(key==3)
	     {  
				 time=0;
         tdttdito();
		     menu3();
	}	
}	      time=1;
        ckcl();
				#endif
		}
}
void menu3()
{       
	      LCD_Clear(WHITE);
				LCD_ShowString(151, 400, "点击充电桩断电或上",BLACK, WHITE);
	      LCD_ShowString(210, 420, "电",BLACK, WHITE);
        ttotc();
			  while(1)
			  {
			  key=KeyScan();
				csd();
				#ifdef USE_CH455_KEY
		    ch455_key = 0xff;
		    while( ch455_key == 0xff )
       {
	     key=KeyScan();
	     if(key==1)
				{
					menu1();
				}
	     if(key==2)
	     {
	       menu2();
	     }
      }	
      ckcl();   
			cpapap();
			#endif
		
		}
}