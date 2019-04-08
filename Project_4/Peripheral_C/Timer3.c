#include "C8051F020.h"
#include "timer3.h"

unsigned int timeUnit = 0;
unsigned long timeTotal = 0;
unsigned char timeFlag = 0;
unsigned char timeThreshold = 10;

void Timer_Init()
{
    CKCON     = 0x20;
    TMR3CN    = 0x02;
//    TMR3RLL   = 0xCD;	 //定时器3计时1ms
//    TMR3RLH   = 0xD4;
	TMR3RLL = 0xAE;	   //定时器计时0.1ms
	TMR3RLH = 0xFB;
}

void OpenTimer3()  //开定时器
{
	TMR3CN|=0x04;
}

void CloseTimer3() //关定时器
{
	TMR3CN&=~0X04;
}

void TIMER3_ISR(void)interrupt 14
{
	TMR3CN &= ~0x80;                     /* TMR3CN.7（TF3）置为0
										TF3：定时器 3 溢出标志   
										当定时器3从0xFFFF到0x0000溢出时由硬件置位。
   									    当定时器3中断被允许时， 该位置‘1’使 CPU 转向定时器 3 的中断服务程序。
									    该位不能由硬件自动清 0， 必须用软件清 0。*/
	timeUnit++;
	if(timeUnit>=timeThreshold)
	{
		timeUnit=0;
//		timeTotal++;
//		P5 ^=0x01; 						//P5.1交替闪亮
		timeFlag = 1;
	}

	
}