#include <msp430g2553.h>
#include "lcd.h"

/***************    键盘驱动    *****************
* PIN 1.4 -- LCD_A0 -- pin6
* PIN 1.5 -- LCD_RST -- pin10
* PIN 1.6 -- LCD_SCL -- pin14
* PIN 1.7 -- LCD_SDA -- pin13       -- by wukk --
************************************************/

#define SetLCDRS  		P1OUT |= BIT4 		 // 引脚 6 宏定义，对LCD_RS进行位操作
#define ClrLCDRS  		P1OUT &= ~BIT4
#define SetLCDRST 		P1OUT |= BIT5		 // 引脚 10 宏定义，对LCD_RST进行位操作
#define ClrLCDRST 		P1OUT &= ~BIT5
#define SETSCL                  P1OUT |= BIT6            // 引脚 14
#define CLRSCL                  P1OUT &= ~BIT6
#define SETSDA                  P1OUT |= BIT7            // 引脚 13
#define CLRSDA                  P1OUT &= ~BIT7
#define derection               P1DIR |= (BIT4+BIT5+BIT6+BIT7); // 
#define BIT(x)  ((0x01) << (x))
    

extern const char AsciiFontData[95][16];
//#pragma location = "CODE_I"
LCDControl  LCDCtl;
//#pragma default


/*
*LCD_init:液晶屏初始化
*传入参数：void
*返回值：void
*/
void LCD_init()
{
    derection;
    SetLCDRST;
    LCD_delayms(10);
    ClrLCDRST;
    LCD_delayms(10);
    SetLCDRST;
    LCD_delayms(10);
    LCD_writeCmd(0xE2);	//软件复位
    LCD_writeCmd(0xA3);//Bais set		显示偏压
    LCD_writeCmd(0xA0);//ADC seg镜像选择 0xa0正常，0xA1左右镜像
    LCD_writeCmd(0xC0);//com output scan direction，com镜像选择 0xc0正常，0xC8上下镜像
    LCD_writeCmd(0x26);
    LCD_delayms(5);
    LCD_writeCmd(0x2C);//内部电源管理，
    LCD_delayms(10);
    LCD_writeCmd(0x2E);//三条指令间隔时间2ms
    LCD_delayms(10);
    LCD_writeCmd(0x2F);
    LCD_delayms(10);
    LCD_writeCmd(0x81);//电压模式选择
    LCD_writeCmd(0x20);//电压调整寄存器低位 范围：0x00-0x3f
    LCD_delayms(10);
    LCD_writeCmd(0xF8);
    LCD_writeCmd(0x01);
    LCD_delayms(5);
    LCD_writeCmd(0xAF);//显示开  
    LCD_clear();    
    LCD_setXY(0,0); 
}
/*
*LCD_delayms:软件实现延时
*传入参数：延时的时间
*返回值：void
*/
void LCD_delayms(unsigned int ms)
{
    int i;
    while(ms--)
    for(i=0;i<=20;i++);
}
/*
*LCD_writeCmd:写指令
*传入参数：写入的指令
*返回值：void
*/
void LCD_writeCmd(unsigned char com)
{
    unsigned char i,j,k;
    ClrLCDRS;  
    for(i=0;i<8;i++)
    { 
         j=com; 
         if(com & BIT7)
             SETSDA;
         else
             CLRSDA;
         CLRSCL;
         for(k = 0;k < 3;k ++);//延时
         SETSCL;
         for(k = 0;k < 3;k ++);//延时     
         com=j<<1;
    }
    SetLCDRS;
}
/*
*LCD_writeData:写数据
*传入参数：写入的数据
*返回值：void
*/
void LCD_writeData(unsigned char dat)

{
	
    unsigned char i,j,k;
    LCDCtl.col++;
    SetLCDRS;  
    for(i=0;i<8;i++)
    { 
         j=dat;
         
         if(dat & BIT7)
             SETSDA;
         else
             CLRSDA;
         CLRSCL;
         for(k = 0;k < 3;k ++);//延时
         SETSCL;  
         for(k = 0;k < 3;k ++);//延时   
         dat=j<<1;
    }
    ClrLCDRS;
}

/*
*LCD_setXY:设置LCD的坐标
*传入参数：横坐标0-127，纵坐标0-7
*返回值：0 正常
*		 -1 传入的坐标错误
*/
char LCD_setXY(unsigned char X, unsigned char Y)
{
    unsigned char msb,lsb;
    if(X > 127 || Y > 7)
    {
        return -1;
    }
    LCD_writeCmd(0xB0 | Y); //页
    msb = X & 0xf0;
    msb = msb >> 4;
    lsb = X & 0x0f;
    LCD_writeCmd(0x10 | msb);  //set Column address MSB
    LCD_writeCmd(0x00 | lsb);  //set column address LSB
    LCDCtl.col = X;
    LCDCtl.row = Y;
    return 0;
}
/*
*LCD_clear: 清屏
*传入参数：void
*返回值：void
*/
void LCD_clear()
{
    unsigned char i;
    for(i = 0 ; i < 4 ; i++)
        LCD_clearLine(i);
}
/*
*LCD_drawPoint: 在屏幕上点亮一个点
*传入参数：横坐标0-127，纵坐标0-63，写入方式
*返回值：0 正常
*		 -1 传入的坐标错误
*/
char LCD_drawPoint(unsigned char x , unsigned char y)
{
    if(x > 127 || y > 64 )
        return -1;
    LCD_setXY( x , y / 8);	
    LCD_writeData(0x01 << (y%8) );
    return 0;
}

/*
*LCD_drawCharAt:在屏幕上指定的坐标上打印一个字符
*传入参数：打印的字符
*		   横坐标：0-15
*		   纵坐标：0-3
*返回值：0 正常
*        -1 传入的坐标错误
*        -2 字符不可打印
*/
char LCD_drawCharAt( char ch , unsigned char col , unsigned char row)
{
    unsigned char i,x,y;
    if(col > 15 || row > 3)
    {
        return -1;
    }
    x = col * 8;
    y = row * 2;
    if(ch == '\n')
    {
        LCD_setXY( 0 , y + 2);
        return 0;
    }
    else if(ch < 0x20 || ch > 0x7e )
    {
        return (char)-2;
    }

    LCD_setXY( x , y);
    for(i = 0 ; i < 8 ; i++)
        LCD_writeData( AsciiFontData[ch - 0x20][i]);
    LCD_setXY( x , y+1);
    for(i = 0 ; i < 8 ; i++)
        LCD_writeData( AsciiFontData[ch - 0x20][i+8]);
    return 0;
}
/*
*LCD_drawChar:在屏幕上指定的坐标上打印一个字符
*传入参数：打印的字符
*返回值：0 正常
*        -1 传入的坐标错误
*        -2 字符不可打印
*/
char LCD_drawChar(char ch)
{
    if(LCDCtl.col > 127)
    {
        LCDCtl.col = 0;
        LCDCtl.row += 2;
    }
    return LCD_drawCharAt(ch , LCDCtl.col / 8 , LCDCtl.row / 2);
}
/*
*LCD_drawStrAt:在屏幕上指定的坐标上打印一个字符串
*传入参数：打印的字符串
*           字符串的长度
*	    横坐标：0-15
*	    纵坐标：0-3
返回值：0 正常
*	-1 打印错误
*	1 字符串的长度为0，不可打印
*/
char LCD_drawStrAt( char * str , unsigned char len , unsigned char col ,
					unsigned char row)
{
    if(0 == len)
    {
        return 1;
    }
    else
    {
        LCD_drawCharAt(*str++ , col , row );
        return LCD_drawStr(str , len - 1);
    }
}
/*
*LCD_drawStr:在屏幕打印一个字符串
*传入参数：打印的字符串
*	    字符串的长度
*返回值：0 正常
*        -1 打印出错
*/
char LCD_drawStr( char * str , unsigned char len)
{
    while(len --)
    {
        if(LCD_drawChar(*str++ ) != 0 )
            return -1;
    }
    return 0;
}
/*
*LCD_clearLine:清除液晶屏上的一行
*传入参数：清除的行：0-3
*返回值：0 正常
*	-1 传入的行错误
*/
char LCD_clearLine(unsigned char row)
{
    unsigned char i = 0;
    if(row > 3)
    {
        return -1;
    }
    for(i = 0 ; i < 16 ; i++)
    {
        LCD_drawCharAt(' ' , i , row );
    }
    return 0;
}
