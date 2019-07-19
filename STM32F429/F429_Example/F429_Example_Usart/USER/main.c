#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "lcd.h"


//ALIENTEK 探索者STM32F407开发板 实验4
//串口通信实验 -库函数版本
//技术支持：www.openedv.com
//淘宝店铺：http://eboard.taobao.com
//广州市星翼电子科技有限公司  
//作者：正点原子 @ALIENTEK


int main(void)
{ 
 
//	u8 t;
//	u8 len;	
	u16 times=0;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);		//延时初始化 
	uart_init(115200);	//串口初始化波特率为115200
	LED_Init();//初始化与LED连接的硬件接口 
	LCD_Init();
	POINT_COLOR=RED;	
		while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			u8 m=USART_RX_BUF[0];
				if(m=='0')
				{
					USART_RX_STA=0;
					printf("\r\nLED0已点亮r\n");					
						while(1)
						{
//							LCD_ShowString(30,40,210,24,24,USART_RX_BUF);
							LED0=0;
							if(USART_RX_STA&0x8000)
							break;
						}
				}
				if(m=='1')		
				{	
					USART_RX_STA=0;
					printf("\r\nLED1已点亮\r\n");
						while(1)
						{
//							LCD_ShowString(30,70,200,16,16,USART_RX_BUF);
							LED1=0;
							if(USART_RX_STA&0x8000)
							break;
						}
				}		
				if(m!='0'&&m!='1')
				{					
					USART_RX_STA=0;
					printf("\r\nLED0、LED1熄灭\r\n");
					while(1)
						{
//							LCD_ShowString(30,90,200,16,16,USART_RX_BUF);
							LED0=1;
							LED1=1;
							if(USART_RX_STA&0x8000)
							break;
						}
				}
			
		}else
		{
			times++;
			if(times%1000==0)printf("\r\n请发送消息\r\n");  
			if(times%50==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
	}	
}

