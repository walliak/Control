#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"


//ALIENTEK 探索者STM32F407开发板 实验3
//按键输入实验-库函数版本 
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司    
//作者：正点原子 @ALIENTEK 


int main(void)
{ 
 
  u8 key;           //保存键值
	delay_init(168);  //初始化延时函数
	LED_Init();				//初始化LED端口 
	BEEP_Init();      //初始化蜂鸣器端口
	KEY_Init();       //初始化与按键连接的硬件接口

	while(1)
	{
		key=KEY_Scan(0);		//得到键值
	   	if(key)
		{						   
			switch(key)
			{				 				
				case KEY1_PRES:	//1秒闪烁
					while(1)
					{
						LED0=!LED0;
						delay_ms(1000);
					}

				case KEY2_PRES:	//0.5秒闪烁	 
					while(1)
					{
						LED0=!LED0;
						delay_ms(500);
					}

				case KEY3_PRES:	//0.1秒闪烁 
					while(1)
					{
						LED0=!LED0;
						delay_ms(100);
					}			

				case KEY4_PRES:	//三种时间切换
					while(1)
					{
						LED0=!LED0;
						delay_ms(1000);
						LED0=!LED0;
						delay_ms(500);
						LED0=!LED0;
						delay_ms(100);						
					}

			}
		}else 
		delay_ms(10); 
	}

}
