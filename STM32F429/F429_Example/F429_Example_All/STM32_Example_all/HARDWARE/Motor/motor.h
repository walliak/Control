#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

//电机输出端口定义
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
	u8 dir;       //方向  0:反转   1:正转
	u16 speed;	  //单位：1/F (s)  ；最大牵引频率 600HZ  空载迁出频率 900HZ

}Motor;

Motor Motor_Init(u8 dir,u16 speed);			//电机参数初始化
void Motor_Out_Init(void);					//输出IO初始化
void TIM4_Motor_Init(Motor motor);
void Motor_Out(u8 CW_Flag,Motor motor);
void TIM4_IRQHandler(void);

#endif
