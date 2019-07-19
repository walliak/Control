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
//    TMR3RLL   = 0xCD;	 //��ʱ��3��ʱ1ms
//    TMR3RLH   = 0xD4;
	TMR3RLL = 0xAE;	   //��ʱ����ʱ0.1ms
	TMR3RLH = 0xFB;
}

void OpenTimer3()  //����ʱ��
{
	TMR3CN|=0x04;
}

void CloseTimer3() //�ض�ʱ��
{
	TMR3CN&=~0X04;
}

void TIMER3_ISR(void)interrupt 14
{
	TMR3CN &= ~0x80;                     /* TMR3CN.7��TF3����Ϊ0
										TF3����ʱ�� 3 �����־   
										����ʱ��3��0xFFFF��0x0000���ʱ��Ӳ����λ��
   									    ����ʱ��3�жϱ�����ʱ�� ��λ�á�1��ʹ CPU ת��ʱ�� 3 ���жϷ������
									    ��λ������Ӳ���Զ��� 0�� ����������� 0��*/
	timeUnit++;
	if(timeUnit>=timeThreshold)
	{
		timeUnit=0;
//		timeTotal++;
//		P5 ^=0x01; 						//P5.1��������
		timeFlag = 1;
	}

	
}