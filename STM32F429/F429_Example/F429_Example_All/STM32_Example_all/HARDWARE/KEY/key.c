#include "key.h"
#include "multi_button.h"
#include "lcd.h"
#include "timer.h"

unsigned int KEY0_Val=1;
unsigned int KEY1_Val=2;
unsigned int KEY2_Val=3;
unsigned int KEY3_Val=4;

struct Button btn1;
struct Button btn2;
struct Button btn3;
struct Button btn4;

unsigned long Time_num=0;

void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	
	//GPIOG 时钟初始化
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化

} 

void Button_Init()
{

	uint8_t(*pin1_level)();
	uint8_t(*pin2_level)();
	uint8_t(*pin3_level)();
	uint8_t(*pin4_level)();
	
	pin1_level = read_button0_GPIO;
	pin2_level = read_button1_GPIO;
	pin3_level = read_button2_GPIO;
	pin4_level = read_button3_GPIO;
	
	button_init(&btn1,pin1_level,0);
	button_init(&btn2,pin2_level,0);
	button_init(&btn3,pin3_level,0);
	button_init(&btn4,pin4_level,0);
	
	button_attach(&btn1, PRESS_DOWN,  BTN1_PRESS_DOWN_Handler);
	button_attach(&btn2, PRESS_DOWN,  BTN2_PRESS_DOWN_Handler);
	button_attach(&btn3, PRESS_DOWN,  BTN3_PRESS_DOWN_Handler);
	button_attach(&btn4, PRESS_DOWN,  BTN4_PRESS_DOWN_Handler);

	button_start(&btn1);
	button_start(&btn2);
	button_start(&btn3);
	button_start(&btn4);
}
/**********************获取按键口电平状态********************/
uint8_t read_button0_GPIO(void)
{	
	return KEY0;
}

uint8_t read_button1_GPIO(void)
{	
	return KEY1;
}

uint8_t read_button2_GPIO(void)
{	
	return KEY2;
}

uint8_t read_button3_GPIO(void)
{	
	return KEY3;
}

/**********************按键功能实现************************/

// 事件：按键按下，每次按下都触发
void BTN1_PRESS_DOWN_Handler(void* btn)
{
		LCD_ShowString(30,80,210,24,24,"a= ");	
		LCD_ShowNum(50,80, KEY0_Val++,2,24);
		TIM3_Int_Init(7000-1,12000-1);
}

void BTN2_PRESS_DOWN_Handler(void* btn)
{
		LCD_ShowString(30,110,210,24,24,"b= ");	
		LCD_ShowNum(50,110, KEY1_Val++,2,24);
}
void BTN3_PRESS_DOWN_Handler(void* btn)
{
		Time_num--;
		TIM_SetCompare2(TIM2,250+30*Time_num);
}

void BTN4_PRESS_DOWN_Handler(void* btn)
{
		Time_num++;
		TIM_SetCompare2(TIM2,250+30*Time_num);
}
