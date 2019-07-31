/*
 *  �������¼����������
*/
#include "msp430g2553.h"    /*��Ƭ���Ĵ���ͷ�ļ�*/
#include "Breath_Lamp_Global.h"	/*ϵͳȫ�ֱ���*/
#include "TA_PWM.h"
/******************************************************************************************************
 * ��       �ƣ�WDT_Ontime()
 * ��       �ܣ�WDT��ʱ�ж��¼���������������WDT��ʱ�жϷ��������һ����ʲô
 * ��ڲ�������
 * ���ڲ�������
 * ˵       ����ʹ���¼�������������ʽ��������ǿ�������ֲ�ԺͿɶ���
 * ��       ������
 ******************************************************************************************************/
void WDT_Ontime()
{
	static int Bright_Delta=0;
	TA0_PWM_SetPermill(1,Bright);	//����PWMռ�ձ�
	if(Bright>=400)								//ռ�ձ����40%�������������Ӿ��仯������
		Bright_Delta=-5;
	if(Bright<=10)								//����
		Bright_Delta=5;
	Bright=Bright+Bright_Delta;
	_nop();												//���ڲ���ϵ���Գ�����
}