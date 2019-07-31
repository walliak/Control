#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"


//ALIENTEK ̽����STM32F407������ ʵ��3
//��������ʵ��-�⺯���汾 
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾    
//���ߣ�����ԭ�� @ALIENTEK 


int main(void)
{ 
 
  u8 key;           //�����ֵ
	delay_init(168);  //��ʼ����ʱ����
	LED_Init();				//��ʼ��LED�˿� 
	BEEP_Init();      //��ʼ���������˿�
	KEY_Init();       //��ʼ���밴�����ӵ�Ӳ���ӿ�

	while(1)
	{
		key=KEY_Scan(0);		//�õ���ֵ
	   	if(key)
		{						   
			switch(key)
			{				 				
				case KEY1_PRES:	//1����˸
					while(1)
					{
						LED0=!LED0;
						delay_ms(1000);
					}

				case KEY2_PRES:	//0.5����˸	 
					while(1)
					{
						LED0=!LED0;
						delay_ms(500);
					}

				case KEY3_PRES:	//0.1����˸ 
					while(1)
					{
						LED0=!LED0;
						delay_ms(100);
					}			

				case KEY4_PRES:	//����ʱ���л�
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
