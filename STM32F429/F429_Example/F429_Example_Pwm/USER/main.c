#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"


//ALIENTEK ̽����STM32F407������ ʵ��9
//PWM���ʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

int main(void)
{ 
	u16 led0pwmval=0;    
	u8 dir=1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
 	TIM2_PWM_Init(499,83);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.     
   while(1) //ʵ�ֱȽ�ֵ��0-300��������300���300-0�ݼ���ѭ��
	{
// 		delay_ms(10);	 
//		if(dir)led0pwmval++;//dir==1 led0pwmval����
//		else led0pwmval--;	//dir==0 led0pwmval�ݼ� 
// 		if(led0pwmval>300)dir=0;//led0pwmval����300�󣬷���Ϊ�ݼ�
//		if(led0pwmval==0)dir=1;	//led0pwmval�ݼ���0�󣬷����Ϊ����
// 
//		TIM_SetCompare2(TIM2,led0pwmval);	//�޸ıȽ�ֵ���޸�ռ�ձ�
	}
}
