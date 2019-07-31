#include "timer.h"
#include "led.h"
#include "delay.h"
#include "lcd.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌĞòÖ»¹©Ñ§Ï°Ê¹ÓÃ£¬Î´¾­×÷ÕßĞí¿É£¬²»µÃÓÃÓÚÆäËüÈÎºÎÓÃÍ¾
//ALIENTEK STM32F407¿ª·¢°å
//¶¨Ê±Æ÷ Çı¶¯´úÂë	   
//ÕıµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//´´½¨ÈÕÆÚ:2014/5/4
//°æ±¾£ºV1.0
//°æÈ¨ËùÓĞ£¬µÁ°æ±Ø¾¿¡£
//Copyright(C) ¹ãÖİÊĞĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 


unsigned long num = 0;
//Í¨ÓÃ¶¨Ê±Æ÷3ÖĞ¶Ï³õÊ¼»¯
//arr£º×Ô¶¯ÖØ×°Öµ¡£
//psc£ºÊ±ÖÓÔ¤·ÖÆµÊı
//¶¨Ê±Æ÷Òç³öÊ±¼ä¼ÆËã·½·¨:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=¶¨Ê±Æ÷¹¤×÷ÆµÂÊ,µ¥Î»:Mhz   Ä¬ÈÏ84MHZ
//ÕâÀïÊ¹ÓÃµÄÊÇ¶¨Ê±Æ÷3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  ///Ê¹ÄÜTIM3Ê±ÖÓ
	
	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//×Ô¶¯ÖØ×°ÔØÖµ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //¶¨Ê±Æ÷·ÖÆµ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //ÏòÉÏ¼ÆÊıÄ£Ê½
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//³õÊ¼»¯TIM3
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //ÔÊĞí¶¨Ê±Æ÷3¸üĞÂÖĞ¶Ï
	TIM_Cmd(TIM3,ENABLE); //Ê¹ÄÜ¶¨Ê±Æ÷3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //¶¨Ê±Æ÷3ÖĞ¶Ï
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //ÇÀÕ¼ÓÅÏÈ¼¶1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //×ÓÓÅÏÈ¼¶3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

// ¶¨Ê±Æ÷2£¬ºÍGPIOE³õÊ¼»¯ 
void RCC_Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
}

// PA1 ¸´ÓÃÎªTIM2_CH2
// PWM Êä³ö
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//¸´ÓÃÊä³öÄ£Ê½
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//ÍÆÍìÊä³ö
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//ÉÏÀ­
		
	GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»

}

//Õ¼¿Õ±È¿É±äµÄPWM²¨  £» ±È½ÏÍ¨µÀ2
// arr:¼ÆÊı³õÖµ 
// psc:Ô¤·ÖÆµÊı
// TIM_Pulse: Õ¼¿Õ±ÈÏà¹Ø²ÎÊı
void TIM2_Configuration(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;

	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//³õÊ¼»¯TIM2
	TIM_PrescalerConfig(TIM2,psc,TIM_PSCReloadMode_Immediate);  //ÉèÖÃÔ¤·ÖÆµÖµ²¢Á¢¼´×°Èë

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_Pulse = 250;

	TIM_OC2Init(TIM2,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable);     //½ûÖ¹Ô¤×°ÔØ¼Ä´æÆ÷

	 //TIM_ITConfig(TIM2,TIM_IT_CC2,ENABLE);									//Ê¹ÄÜTIMÖĞ
	TIM_ARRPreloadConfig(TIM2,ENABLE);

	TIM_Cmd(TIM2,ENABLE);	 	

}

//¶¨Ê±Æ÷3ÖĞ¶Ï·şÎñº¯Êı
void TIM3_IRQHandler(void)
{
	//Time_num++;
	//TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //Çå³ıÖĞ¶Ï±êÖ¾Î»
}
