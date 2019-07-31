#include "sys.h" 
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"
#include "multi_button.h"
#include "exit.h"
#include "timer.h"
#include "motor.h"

// LCD��ʾ��Ҫ�������ڣ������޷���ʾ

extern unsigned char  eightCCW[8];
extern unsigned char  eightCW[8];
//ÿ��������ֵ
//extern unsigned int KEY0_Val; 
//extern unsigned int KEY0_Val; 
//extern unsigned int KEY0_Val; 
//extern unsigned int KEY0_Val; 

//���尴����ʹ��MultiButton ģ��
// https://github.com/0x1abin/MultiButton/blob/master/README.md
//extern	struct Button btn1;
//extern	struct Button btn2;
//extern	struct Button btn3;
//extern	struct Button btn4;

extern  struct Motor motor;
extern unsigned long Time_num;
RCC_ClocksTypeDef get_rcc_clock;


/***********************************************����+LCD************************************************/

//int main(void)
//{ 
//	u8 key=6;
//	u8 timer_ticks =0;    

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
//	delay_init(168);      //��ʼ����ʱ����
//	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200

//	LED_Init();					  //��ʼ��LED
// 	LCD_Init();           //��ʼ��LCD FSMC�ӿ�
//	POINT_COLOR=RED;      //������ɫ����ɫ
//	EXIT_KEY_Init();			//�жϳ�ʼ��
//	Button_Init();				//������ʼ��
//	//RCC_GetClocksFreq(&get_rcc_clock);    // �鿴ʱ��ԴƵ�� 
//	//TIM3_Int_Init(7000-1,12000-1);
//	
//	while(1) 
//	{
//		timer_ticks++;
//		if(timer_ticks == 5) {
//       timer_ticks = 0;
//       LCD_ShowString(30,40,210,24,24,"Welcome!");
//		   LCD_ShowNum(50,280, Time_num,4,24);
//       button_ticks();  
//    }
//	}
//}


/***********************************************��������PWN���ռ�ձ�************************************************/
//int main(void)
//{
//	u8 timer_ticks =0;  
//	EXIT_KEY_Init();			//�жϳ�ʼ��
//	Button_Init();				//������ʼ��
//	delay_init(168);      //��ʼ����ʱ����
//	RCC_Configuration();

//	TIM2_Configuration(500,84-1);
//	GPIO_Configuration();
//	while(1)
//	{
//	     delay_ms(10);	
//		 button_ticks();  
//		
//	}
//}

/***********************************************�������ģ�����************************************************/
int main()
{
	motor = Motor_Init(0,600);
	delay_init(168);      //��ʼ����ʱ����
	TIM4_Motor_Init(motor);
	while(1);
	
	
}
