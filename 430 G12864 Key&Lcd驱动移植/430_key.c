/*2019年4月20日胡文杰移植的G12864板子KEY模块*/
/*移植修改部分仅仅只是IO口的配置和去掉少部分代码*/
#include "io430.h"



void KeyPort_Init ()
{
   P3DIR |= 0x07 ; //P3.0-P3.2设置为输出方向

   P3DIR &= ~0x70; //P3.4-P3.6设置成输入方向  
   P3REN |= 0x70;  //设置上拉电阻

   P3OUT |= 0x70;
	 
}


/**********************************************************************************************************
* 函数名称：KeyScan
* 函数功能：按键扫描，返回0表示无键按下，1-9是正常返回
**********************************************************************************************************/
unsigned char KeyScan(void)
{
  unsigned long i;
  unsigned char P3 ;
  P3 = P3OUT;
  P3OUT = (P3 &0x80)|(P3 &0x08) | 0x00;  //此段代码配合12864板子原理图一起食用效果更佳
  if(0x70 == (P3IN & 0x70)) // 没有按键，返回0
  {
    return 0;
  }
 
  for(i = 0;i < 12000;i ++);  // 有键按下，延时先 可修改
  
 // 扫描KEY1 - KEY3
  P3 = P3OUT;
  P3OUT = (P3 & 0x80)|(P3 & 0x08) | 0x06;
  if(0x70 != (P3IN & 0x70)) 
  {
    switch((P3IN & 0x70))
    {
    case 0x60:
      return 1;
    case 0x50:
      return 2;
    case 0x30:
      return 3;      
  
    default:
      return 0; 
    }
  } 

  // 扫描KEY4 - KEY6
  P3 = P3OUT;
  P3OUT = (P3&0x80)|(P3 &0x08) | 0x05;
  if(0x70 != (P3IN & 0x70))
  {
    switch((P3IN & 0x70))
    {
    case 0x60:
      return 4;
    case 0x50:
      return 5;
    case 0x30:
      return 6;     
    default:
      return 0; 
    }
  }    

  // 扫描KEY7 - KEY9
  P3 = P3OUT;
  P3OUT = (P3&0x80)|(P3 &0x08) | 0x03;
  if(0x70 != (P3IN & 0x70)) 
  {
    switch((P3IN & 0x70))
    {
    case 0x60:
      return 7;
    case 0x50:
      return 8;
    case 0x30:
      return 9;      
    default:
      return 0; 
    }
  }  
  return 0;
}