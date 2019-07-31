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

// LCD显示需要开启串口，否则无法显示

extern unsigned char  eightCCW[8];
extern unsigned char  eightCW[8];
//每个按键的值
//extern unsigned int KEY0_Val; 
//extern unsigned int KEY0_Val; 
//extern unsigned int KEY0_Val; 
//extern unsigned int KEY0_Val; 

//定义按键，使用MultiButton 模组
// https://github.com/0x1abin/MultiButton/blob/master/README.md
//extern	struct Button btn1;
//extern	struct Button btn2;
//extern	struct Button btn3;
//extern	struct Button btn4;

extern  struct Motor motor;
extern unsigned long Time_num;
RCC_ClocksTypeDef get_rcc_clock;


/***********************************************按键+LCD************************************************/

//int main(void)
//{ 
//	u8 key=6;
//	u8 timer_ticks =0;    

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
//	delay_init(168);      //初始化延时函数
//	uart_init(115200);		//初始化串口波特率为115200

//	LED_Init();					  //初始化LED
// 	LCD_Init();           //初始化LCD FSMC接口
//	POINT_COLOR=RED;      //画笔颜色：红色
//	EXIT_KEY_Init();			//中断初始化
//	Button_Init();				//按键初始化
//	//RCC_GetClocksFreq(&get_rcc_clock);    // 查看时钟源频率 
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


/***********************************************按键控制PWN输出占空比************************************************/
//int main(void)
//{
//	u8 timer_ticks =0;  
//	EXIT_KEY_Init();			//中断初始化
//	Button_Init();				//按键初始化
//	delay_init(168);      //初始化延时函数
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

/***********************************************电机驱动模块测试************************************************/
int main()
{
	motor = Motor_Init(0,600);
	delay_init(168);      //初始化延时函数
	TIM4_Motor_Init(motor);
	while(1);
	
	
}
