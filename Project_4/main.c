#include "math.h"
#include "init.h"
#include "lcd.h"
#include "key.h"
#include "timer3.h"
#include "C8051F020.h"

//����	CCW = CounterClockWise ; CW = ClockWise;
 unsigned char code eightCCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};   //��ʱ����ת����� 
 unsigned char code eightCW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    //��ʱ����ת�����

//����
 unsigned char code fourCCW[4]={0x01,0x08,0x04,0x02};
 unsigned char code fourCW[4]={0x02,0x04,0x08,0x01};
 void Motor_CCW();
 void Motor_CW();
 void StopMotor();
 void Show();

void Main()
{	
	 uchar key=0,flag=0;
	 int i,N=64;
	 	 
	 Init_Device();	 	 
     DrawcharS("Project-4",1,4);
     DrawcharS("3.28--4.16",2,4);        				
	 DelayMSec(1000);
	 Clear();
	 P7=0x00;			  	
	 while(1)
	 {	
	 	Show();	 	
	 	key = KeyScan();
		if(key!=0)
		{
			switch(key)
			{
			 	case 1:	//˳ʱ��ת
						Clear(); //����
						Show(); 			
						while(1)
						{
							DrawhanziS("6",0,0);
							Motor_CW();
							flag=KeyScan();							
							if(flag==9)
							break;							
						}
						flag=0;
						Clear();
						break;
				case 2:	//��ʱ��ת
						Clear(); //����
						Show(); 						
						while(1)
						{
							DrawhanziS("6",1,0);
							Motor_CCW();
							flag=KeyScan();
							if(flag==9)
							break;							
						}
						flag=0;
						Clear();
						break;
				case 3:	//ת1/4Ȧ
						Clear(); //���� 
						DrawhanziS("6",2,0);				
						for(i=0;i<N/4;i++)
						{
							Motor_CW();
						}
						Clear();
						break;
				case 4://ת1/8Ȧ
						Clear(); //���� 
						DrawhanziS("6",3,0);						
						for(i=0;i<N/8;i++)
						{
							Motor_CCW();
						}
						Clear();
						break;
				case 5://����ת��
						Clear();

				case 9://
						StopMotor();
						break;
			
				default:break;

			}
		}
	 } 
}

//�����תһ�ܣ�����������������һ�ܣ�������Ĵ�����ת��һ��
//��ת8��
void Motor_CW(void)
{
  uchar i,j;
  for(j=0;j<8;j++)
  {	
  	for(i=0;i<8;i++)
	{
		while(1)
		{
			P7=eightCW[i];
		   	if(timeFlag==1)
			{
				timeFlag=0;
				break;
			}
		}
	}
	   
  }
}

//��ת8��
void Motor_CCW(void)
{
  uchar i,j;
  for(j=0;j<8;j++)     
  {  
  	for(i=0;i<8;i++)	
	 {
	 	while(1)
		{
			P7=eightCCW[i];
		   	if(timeFlag==1)
			{
				timeFlag=0;
				break;
			}
		}
	   
	 }
  }
}

void StopMotor(void)
{
	P7=0x00;
}

void Show()
{
	DrawcharS("1.",0,0),DrawhanziS("0234",0,1);
	DrawcharS("2.",1,0),DrawhanziS("1234",1,1);
	DrawcharS("3.",2,0),DrawhanziS("4",2,1),DrawcharS("1/4",2,4),DrawhanziS("5",2,4);
	DrawcharS("4.",3,0),DrawhanziS("4",3,1),DrawcharS("1/8",3,4),DrawhanziS("5",3,4);
}

void ShowSpeed()
{
 	
}