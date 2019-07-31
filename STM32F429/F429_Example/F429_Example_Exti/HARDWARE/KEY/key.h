#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

/*����ķ�ʽ��ͨ��ֱ�Ӳ����⺯����ʽ��ȡIO*/

#define KEY1 		GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2)	//PG2
#define KEY2 		GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_3) //PG3
#define KEY3 		GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_4)	//PG4
#define KEY4 		GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_5) //PG5

/*���淽ʽ��ͨ��λ��������ʽ��ȡIO*/
/*
#define KEY0 		PEin(4)   //PE4
#define KEY1 		PEin(3)		//PE3 
#define KEY2 		PEin(2)		//P32
#define WK_UP 	PAin(0)		//PA0
*/


#define KEY1_PRES	1
#define KEY2_PRES	2
#define KEY3_PRES	3
#define KEY4_PRES 4

void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(u8);  		//����ɨ�躯��	

#endif