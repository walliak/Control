#include <msp430g2553.h>
#include "lcd.h"

/***************    ��������    *****************
* PIN 1.4 -- LCD_A0 -- pin6
* PIN 1.5 -- LCD_RST -- pin10
* PIN 1.6 -- LCD_SCL -- pin14
* PIN 1.7 -- LCD_SDA -- pin13       -- by wukk --
************************************************/

#define SetLCDRS  		P1OUT |= BIT4 		 // ���� 6 �궨�壬��LCD_RS����λ����
#define ClrLCDRS  		P1OUT &= ~BIT4
#define SetLCDRST 		P1OUT |= BIT5		 // ���� 10 �궨�壬��LCD_RST����λ����
#define ClrLCDRST 		P1OUT &= ~BIT5
#define SETSCL                  P1OUT |= BIT6            // ���� 14
#define CLRSCL                  P1OUT &= ~BIT6
#define SETSDA                  P1OUT |= BIT7            // ���� 13
#define CLRSDA                  P1OUT &= ~BIT7
#define derection               P1DIR |= (BIT4+BIT5+BIT6+BIT7); // 
#define BIT(x)  ((0x01) << (x))
    

extern const char AsciiFontData[95][16];
//#pragma location = "CODE_I"
LCDControl  LCDCtl;
//#pragma default


/*
*LCD_init:Һ������ʼ��
*���������void
*����ֵ��void
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
    LCD_writeCmd(0xE2);	//�����λ
    LCD_writeCmd(0xA3);//Bais set		��ʾƫѹ
    LCD_writeCmd(0xA0);//ADC seg����ѡ�� 0xa0������0xA1���Ҿ���
    LCD_writeCmd(0xC0);//com output scan direction��com����ѡ�� 0xc0������0xC8���¾���
    LCD_writeCmd(0x26);
    LCD_delayms(5);
    LCD_writeCmd(0x2C);//�ڲ���Դ����
    LCD_delayms(10);
    LCD_writeCmd(0x2E);//����ָ����ʱ��2ms
    LCD_delayms(10);
    LCD_writeCmd(0x2F);
    LCD_delayms(10);
    LCD_writeCmd(0x81);//��ѹģʽѡ��
    LCD_writeCmd(0x20);//��ѹ�����Ĵ�����λ ��Χ��0x00-0x3f
    LCD_delayms(10);
    LCD_writeCmd(0xF8);
    LCD_writeCmd(0x01);
    LCD_delayms(5);
    LCD_writeCmd(0xAF);//��ʾ��  
    LCD_clear();    
    LCD_setXY(0,0); 
}
/*
*LCD_delayms:���ʵ����ʱ
*�����������ʱ��ʱ��
*����ֵ��void
*/
void LCD_delayms(unsigned int ms)
{
    int i;
    while(ms--)
    for(i=0;i<=20;i++);
}
/*
*LCD_writeCmd:дָ��
*���������д���ָ��
*����ֵ��void
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
         for(k = 0;k < 3;k ++);//��ʱ
         SETSCL;
         for(k = 0;k < 3;k ++);//��ʱ     
         com=j<<1;
    }
    SetLCDRS;
}
/*
*LCD_writeData:д����
*���������д�������
*����ֵ��void
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
         for(k = 0;k < 3;k ++);//��ʱ
         SETSCL;  
         for(k = 0;k < 3;k ++);//��ʱ   
         dat=j<<1;
    }
    ClrLCDRS;
}

/*
*LCD_setXY:����LCD������
*���������������0-127��������0-7
*����ֵ��0 ����
*		 -1 ������������
*/
char LCD_setXY(unsigned char X, unsigned char Y)
{
    unsigned char msb,lsb;
    if(X > 127 || Y > 7)
    {
        return -1;
    }
    LCD_writeCmd(0xB0 | Y); //ҳ
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
*LCD_clear: ����
*���������void
*����ֵ��void
*/
void LCD_clear()
{
    unsigned char i;
    for(i = 0 ; i < 4 ; i++)
        LCD_clearLine(i);
}
/*
*LCD_drawPoint: ����Ļ�ϵ���һ����
*���������������0-127��������0-63��д�뷽ʽ
*����ֵ��0 ����
*		 -1 ������������
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
*LCD_drawCharAt:����Ļ��ָ���������ϴ�ӡһ���ַ�
*�����������ӡ���ַ�
*		   �����꣺0-15
*		   �����꣺0-3
*����ֵ��0 ����
*        -1 ������������
*        -2 �ַ����ɴ�ӡ
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
*LCD_drawChar:����Ļ��ָ���������ϴ�ӡһ���ַ�
*�����������ӡ���ַ�
*����ֵ��0 ����
*        -1 ������������
*        -2 �ַ����ɴ�ӡ
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
*LCD_drawStrAt:����Ļ��ָ���������ϴ�ӡһ���ַ���
*�����������ӡ���ַ���
*           �ַ����ĳ���
*	    �����꣺0-15
*	    �����꣺0-3
����ֵ��0 ����
*	-1 ��ӡ����
*	1 �ַ����ĳ���Ϊ0�����ɴ�ӡ
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
*LCD_drawStr:����Ļ��ӡһ���ַ���
*�����������ӡ���ַ���
*	    �ַ����ĳ���
*����ֵ��0 ����
*        -1 ��ӡ����
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
*LCD_clearLine:���Һ�����ϵ�һ��
*���������������У�0-3
*����ֵ��0 ����
*	-1 ������д���
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
