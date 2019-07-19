/**
		�����������ģ��
ע�⣺�����ʱ��Ҫ����λ�á�
		  
**/

#include "motor.h"

unsigned char  eightCCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};   //��ʱ����ת����� 
unsigned char  eightCW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    //��ʱ����ת�����

u8 CW_Flag = 0; 	//������־
Motor motor;

Motor Motor_Init(u8 dir,u16 speed)
{
	Motor motor;
	motor.dir = dir;
	motor.speed = speed;
	return motor;
}

//��ʱ��4��ʼ�����������������
void TIM4_Motor_Init(Motor motor)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	Motor_Out_Init();
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///ʹ��TIM4ʱ��
	
	TIM_TimeBaseInitStructure.TIM_Period = 12000/motor.speed; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=8400;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//��ʼ��TIM4
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //����ʱ��4�����ж�
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��4
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //��ʱ��4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


//IO�ڳ�ʼ�� PF 1,2,3,4,5,6,7,8
void Motor_Out_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4
	|GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
		
	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��
}


//IO�����һ�ε��ת������
void Motor_Out(u8 CW_Flag,Motor motor)
{
	switch (motor.dir)
	{
		case 0:		//��ת	
				Motor1_OUT1 = (eightCCW[CW_Flag]>> 3) & 0x01;
				Motor1_OUT2 = (eightCCW[CW_Flag]>> 2) & 0x01;
				Motor1_OUT3 = (eightCCW[CW_Flag]>> 1) & 0x01;
				Motor1_OUT4 = (eightCCW[CW_Flag]) 	 & 0x01;
				break;
		case 1:		//��ת	
				Motor1_OUT1 = (eightCW[CW_Flag]>> 3) & 0x01;
				Motor1_OUT2 = (eightCW[CW_Flag]>> 2) & 0x01;
				Motor1_OUT3 = (eightCW[CW_Flag]>> 1) & 0x01;
				Motor1_OUT4 = (eightCW[CW_Flag]) 	 & 0x01;
				break;
	}
}



//��ʱ��4�жϷ�����
void TIM4_IRQHandler(void)
{
	if(CW_Flag == 8)
		CW_Flag =0;
	Motor_Out(CW_Flag,motor);					//IO���������
	CW_Flag++;
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //����жϱ�־λ
}
