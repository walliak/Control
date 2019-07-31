#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

//�������˿ڶ���
#define Motor1_OUT1  PFout(1)  
#define Motor1_OUT2  PFout(2)  
#define Motor1_OUT3  PFout(3)  
#define Motor1_OUT4  PFout(4)  

#define Motor2_OUT1  PFout(5)  
#define Motor2_OUT2  PFout(6)  
#define Motor2_OUT3  PFout(7)  
#define Motor2_OUT4  PFout(8) 




typedef struct Motor
{
	u8 dir;       //����  0:��ת   1:��ת
	u16 speed;	  //��λ��1/F (s)  �����ǣ��Ƶ�� 600HZ  ����Ǩ��Ƶ�� 900HZ

}Motor;

Motor Motor_Init(u8 dir,u16 speed);			//���������ʼ��
void Motor_Out_Init(void);					//���IO��ʼ��
void TIM4_Motor_Init(Motor motor);
void Motor_Out(u8 CW_Flag,Motor motor);
void TIM4_IRQHandler(void);

#endif
