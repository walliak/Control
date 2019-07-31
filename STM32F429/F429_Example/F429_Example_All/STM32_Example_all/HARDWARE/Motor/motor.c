/**
		步进电机驱动模块
注意：电机延时需要考虑位置。
		  
**/

#include "motor.h"

unsigned char  eightCCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};   //逆时钟旋转相序表 
unsigned char  eightCW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    //正时钟旋转相序表

u8 CW_Flag = 0; 	//相序表标志
Motor motor;

Motor Motor_Init(u8 dir,u16 speed)
{
	Motor motor;
	motor.dir = dir;
	motor.speed = speed;
	return motor;
}

//定时器4初始化，处理电机脉冲输出
void TIM4_Motor_Init(Motor motor)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	Motor_Out_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM4时钟
	
	TIM_TimeBaseInitStructure.TIM_Period = 12000/motor.speed; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=8400;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//初始化TIM4
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器4更新中断
	TIM_Cmd(TIM4,ENABLE); //使能定时器4
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


//IO口初始化 PF 1,2,3,4,5,6,7,8
void Motor_Out_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4
	|GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
		
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化
}


//IO口输出一次电机转动脉冲
void Motor_Out(u8 CW_Flag,Motor motor)
{
	switch (motor.dir)
	{
		case 0:		//反转	
				Motor1_OUT1 = (eightCCW[CW_Flag]>> 3) & 0x01;
				Motor1_OUT2 = (eightCCW[CW_Flag]>> 2) & 0x01;
				Motor1_OUT3 = (eightCCW[CW_Flag]>> 1) & 0x01;
				Motor1_OUT4 = (eightCCW[CW_Flag]) 	 & 0x01;
				break;
		case 1:		//正转	
				Motor1_OUT1 = (eightCW[CW_Flag]>> 3) & 0x01;
				Motor1_OUT2 = (eightCW[CW_Flag]>> 2) & 0x01;
				Motor1_OUT3 = (eightCW[CW_Flag]>> 1) & 0x01;
				Motor1_OUT4 = (eightCW[CW_Flag]) 	 & 0x01;
				break;
	}
}



//定时器4中断服务函数
void TIM4_IRQHandler(void)
{
	if(CW_Flag == 8)
		CW_Flag =0;
	Motor_Out(CW_Flag,motor);					//IO口输出脉冲
	CW_Flag++;
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
}
