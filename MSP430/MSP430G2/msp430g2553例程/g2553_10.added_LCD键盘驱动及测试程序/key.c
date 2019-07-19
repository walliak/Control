#include <msp430g2553.h>

#include "key.h"



/***************    键盘驱动    *****************
* VCC --- 液晶复位 pin11

* PIN 2.0 -- A1 -- pin1
* PIN 2.1 -- A2 -- pin3
* PIN 2.2 -- A3 -- pin5
* PIN 2.3 -- B1 -- pin7
* PIN 2.4 -- B2 -- pin8
* PIN 2.5 -- B3 -- pin9             -- by akai --
************************************************/

/**********************************************************************************************************
* 函数名称：KeyPort_Init
* 函数功能：使用键盘前必须调用的初始化函数
**********************************************************************************************************/
void KeyPort_Init ()
{
  P2DIR |= (BIT0 + BIT1 + BIT2); // PA 0,1,2 输出
  P2OUT &= ~(BIT0 + BIT1 + BIT2); // PA 0,1,2 输出低电平
  
  P2DIR &= ~(BIT3 + BIT4 + BIT5); // PB 0,1,2 输入
  P2REN |= (BIT3 + BIT4 + BIT5); // PB 0,1,2 使能拉电阻
  P2OUT |= (BIT3 + BIT4 + BIT5); // PB 0,1,2 上拉
}

/**********************************************************************************************************
* 函数名称：KeyScan
* 函数功能：按键扫描，返回0表示无键按下，1-9是正常返回
**********************************************************************************************************/
unsigned char KeyScan()
{
  unsigned long i; // 内部计数变量
  
  P2OUT &= ~(BIT0 + BIT1 + BIT2); // PA 0,1,2 输出低电平
  if( (0!=(P2IN & BIT3)) && (0!=( P2IN & BIT4 )) && (0!=( P2IN & BIT5)) ) // 没有按键，返回0 
  {
    return 0;
  }
  else // 有键按下，延时先
  {    
    for( i = 0 ; i < 1000 ; i ++ );  // 软件延时消抖
    
    P2OUT &= ~(BIT0); // PA 1 输出低电平
    P2OUT |= (BIT1 + BIT2); // PA 2,3 输出高电平
  
    switch( P2IN & (BIT3 + BIT4 + BIT5) )
    {
    case 0x30:return 1;break;
    case 0x28:return 2;break;
    case 0x18:return 3;break;
    default:break;
    }
    
    P2OUT &= ~(BIT1); // PA 2 输出低电平
    P2OUT |= (BIT0 + BIT2); // PA 1,3 输出高电平
  
    switch( P2IN & (BIT3 + BIT4 + BIT5) )
    {
    case 0x30:return 4;break;
    case 0x28:return 5;break;
    case 0x18:return 6;break;
    default:break;
    }
    
    P2OUT &= ~(BIT2); // PA 3 输出低电平
    P2OUT |= (BIT0 + BIT1); // PA 1,2 输出高电平
  
    switch( P2IN & (BIT3 + BIT4 + BIT5) )
    {
    case 0x30:return 7;break;
    case 0x28:return 8;break;
    case 0x18:return 9;break;
    default:break;
    }
    
    return 0;
  }
} 
  