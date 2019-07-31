#include "C8051F020.h"
#include "timer3.h"

unsigned int ms=0;
unsigned long sTotal=0;


void TIMER3_ISR(void)interrupt 14
{
	TMR3CN &= ~0x80;                     /* TMR3CN.7��TF3����Ϊ0
										TF3����ʱ�� 3 �����־   
										����ʱ��3��0xFFFF��0x0000���ʱ��Ӳ����λ��
   									    ����ʱ��3�жϱ�����ʱ�� ��λ�á�1��ʹ CPU ת��ʱ�� 3 ���жϷ������
									    ��λ������Ӳ���Զ��� 0�� ����������� 0��*/
	ms++;
	if(ms>999)
	{
		ms=0;
		sTotal++;
		P5 ^=0x01; 						//P5.1��������

	}


}