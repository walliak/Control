#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "lcd.h"


//ALIENTEK ̽����STM32F407������ ʵ��4
//����ͨ��ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK


int main(void)
{ 
 
//	u8 t;
//	u8 len;	
	u16 times=0;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);		//��ʱ��ʼ�� 
	uart_init(115200);	//���ڳ�ʼ��������Ϊ115200
	LED_Init();//��ʼ����LED���ӵ�Ӳ���ӿ� 
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
					printf("\r\nLED0�ѵ���r\n");					
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
					printf("\r\nLED1�ѵ���\r\n");
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
					printf("\r\nLED0��LED1Ϩ��\r\n");
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
			if(times%1000==0)printf("\r\n�뷢����Ϣ\r\n");  
			if(times%50==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
	}	
}

