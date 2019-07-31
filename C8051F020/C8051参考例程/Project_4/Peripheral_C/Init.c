#include"init.h"
#include "key.h"
#include "Timer3.h"
#include "lcd.h"
#include "C8051F020.h"

void Reset_Sources_Init()
{
    WDTCN     = 0xDE;
    WDTCN     = 0xAD;
    RSTSRC    = 0x04;
}

void Voltage_Reference_Init()
{
    REF0CN    = 0x03;
}

void Port_IO_Init()
{
	/* 位 6： XBARE：交叉开关使能位   
	0：交叉开关禁止。端口 0、1、2 和 3 的所有引脚被强制为输入方式。 
	1：交叉开关使能。
	*/
	XBR2      = 0x40;

	/*
	位 7-0： P3MDOUT.[7:0]：端口 3 输出方式位。   
	0：端口引脚的输出方式为漏极开路。 
	1：端口引脚的输出方式为推挽。
	LCD屏使用了P3.4、P3.5,推挽输出。
	*/
    P3MDOUT   = 0x30;								
    
	P74OUT = 0x50;							 
}

void Oscillator_Init()
{
    int i = 0;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x08;
}

void Interrupts_Init() 				
{									
    IE        = 0x80;//打开总的中断
    EIE2      = 0x01;//打开定时器3的中断
}

// Initialization function for device,
// Call Init_Device() from your main program
void Init_Device(void)
{
    Reset_Sources_Init();
    Timer_Init(); 
	OpenTimer3();
    Voltage_Reference_Init();
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
	newLCDInit();
}

void DelayOneSecond(void)//延时1s
{
 unsigned long a;
 for(a=0;a<153600;a++);
}

void DelayMSec(int time)
{
	int a ;
	while(time--)
	{
		for(a=0;a<150;a++);	//大约延时1ms
	}
}

void DelayPart(int time)
{
	int a;
	while(time--)
	{
		for(a=0;a<15;a++);//大约延时0.1ms
	}	
}