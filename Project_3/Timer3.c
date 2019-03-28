#include "C8051F020.h"
#include "timer3.h"

unsigned int ms=0;
unsigned long sTotal=0;


void TIMER3_ISR(void)interrupt 14
{
	TMR3CN &= ~0x80;                     /* TMR3CN.7（TF3）置为0
										TF3：定时器 3 溢出标志   
										当定时器3从0xFFFF到0x0000溢出时由硬件置位。
   									    当定时器3中断被允许时， 该位置‘1’使 CPU 转向定时器 3 的中断服务程序。
									    该位不能由硬件自动清 0， 必须用软件清 0。*/
	ms++;
	if(ms>999)
	{
		ms=0;
		sTotal++;
		P5 ^=0x01; 						//P5.1交替闪亮

	}


}