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
	/* λ 6�� XBARE�����濪��ʹ��λ   
	0�����濪�ؽ�ֹ���˿� 0��1��2 �� 3 ���������ű�ǿ��Ϊ���뷽ʽ�� 
	1�����濪��ʹ�ܡ�
	*/
	XBR2      = 0x40;

	/*
	λ 7-0�� P3MDOUT.[7:0]���˿� 3 �����ʽλ��   
	0���˿����ŵ������ʽΪ©����·�� 
	1���˿����ŵ������ʽΪ���졣
	LCD��ʹ����P3.4��P3.5,���������
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
    IE        = 0x80;//���ܵ��ж�
    EIE2      = 0x01;//�򿪶�ʱ��3���ж�
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

void DelayOneSecond(void)//��ʱ1s
{
 unsigned long a;
 for(a=0;a<153600;a++);
}

void DelayMSec(int time)
{
	int a ;
	while(time--)
	{
		for(a=0;a<150;a++);	//��Լ��ʱ1ms
	}
}

void DelayPart(int time)
{
	int a;
	while(time--)
	{
		for(a=0;a<15;a++);//��Լ��ʱ0.1ms
	}	
}