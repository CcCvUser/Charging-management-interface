#include "mp3.h"
#include "USART3.h"

void setMp3Dev(unsigned char dev)
{
    unsigned char device[5]  = {0x7E, 0x03, 0x09, 0x00, 0xEF};      // 指定设备 0：U 4:FLASH
    device[3] = dev;
    USART6_Senddata(device, 5);
}

void setMp3Vol(unsigned char vol)
{
    unsigned char volume[5]  = {0x7E, 0x03, 0x06, 0x00, 0xEF};      //	音量 0-30
    volume[3] = vol;
    USART6_Senddata(volume, 5);
}

void mp3Play(void)
{
    unsigned char Play[4]  = {0x7E, 0x02, 0x0D, 0xEF};                  //	播放
    USART6_Senddata(Play, 4); 
}

void mp3Stop(void)
{
    unsigned char Stop[4]  = {0x7E, 0x02, 0x02, 0xEF};                  //	停止
    USART6_Senddata(Stop, 4); 
}
void mp3Play1(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x01, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play2(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x02, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play3(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x03, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play4(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x04, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play5(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x05, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play6(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x06, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play7(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x07, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play8(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x08, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play9(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x09, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play10(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x10, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play11(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x11, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play12(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x12, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play13(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x13, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play14(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x14, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play15(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x15, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}
void mp3Play16(void)
{
    unsigned char Play1[6]  = {0x7E, 0x04, 0x42, 0x02, 0x16, 0xEF};                  //	播放
    USART6_Senddata(Play1, 6); 
}


