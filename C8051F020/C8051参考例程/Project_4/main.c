#include "math.h"
#include "init.h"
#include "lcd.h"
#include "key.h"
#include "timer3.h"
#include "compositechars.h"
#include "C8051F020.h"

//八拍	CCW = CounterClockWise ; CW = ClockWise;
 unsigned char code eightCCW[8]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};   //逆时钟旋转相序表 
 unsigned char code eightCW[8]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};    //正时钟旋转相序表

//四拍
 unsigned char code fourCCW[4]={0x01,0x08,0x04,0x02};
 unsigned char code fourCW[4]={0x02,0x04,0x08,0x01};

 uchar pageFlag ;
 uchar str_f[5],str_s[5],str_n[5];
 uint frequency;
 ulong speed;

 void Motor_CCW();
 void Motor_CW();
 void Double_Up();
 void Double_Down();
 void StopMotor();
 void Show();
 void Caculate();

void Main()
{	
	 uchar key=0,flag=0;
	 int i=0,N=64;
	 	 
	 Init_Device();	 	 
     DrawcharS("Project-4",1,4);
     DrawcharS("3.28--4.16",2,4);        				
	 DelayMSec(1000);
	 pageFlag=0;
	 Caculate();
	 Clear();
	 	 			  	
	 while(1)
	 {	
	 	Show();	 	
	 	key = KeyScan();
		if(key!=0)
		{
			switch(key)
			{
			 	case 1:	//顺时针转
						Clear(); //清屏
						Show();
						DrawhanziS("6",0,0); 			
						while(1)
						{
//							Motor_CW();
							Double_Up();
							flag=KeyScan();							
							if(flag==1)
							{
								StopMotor();
								break;	
							}							
						}
						flag=0;
						Clear();
						break;
				case 2:	//逆时针转
						Clear(); //清屏
						Show();
						DrawhanziS("6",1,0); 						
						while(1)
						{							
//							Motor_CCW();
							Double_Down();
							flag=KeyScan();
							if(flag==2)
						   	{
								StopMotor();
								break;
							}														
						}
						flag=0;
						Clear();
						break;
				case 3:	//转1/4圈
						DrawhanziS("6",2,0);				
						for(i=0;i<N/4;i++)
						{
							Motor_CW();
						}
						Clear();
						break;
				case 4://转1/8圈
						DrawhanziS("6",3,0);						
						for(i=0;i<N/8;i++)
						{
							Motor_CCW();
						}
						Clear();
						break;
				case 6://						
						timeThreshold++;					
						if(timeThreshold>=20)
						{
							timeThreshold=20;
						}
						Caculate();
						Clear();
						break;
				case 7://
						timeThreshold--;						
						if(timeThreshold<=5)
						{
							timeThreshold = 5;
						}
						Caculate();
						Clear();
						break;
				case 9://
						pageFlag ++;
						if(pageFlag == 100)
						{
							pageFlag = 0;
						}
						Clear();
						break;			
				default:break;

			}
		}
	 } 
}
//电机旋转一周，不是外面所看到的一周，是里面的传动轮转了一周
//正转8拍
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

//反转8拍
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

void Double_Up(void)
{
  uchar i,j;
  for(j=0;j<8;j++)
  {	
  	for(i=0;i<8;i++)
	{
		while(1)
		{
			P7=eightCW[i];
			P6=eightCCW[i];
		   	if(timeFlag==1)
			{
				timeFlag=0;
				break;
			}
		}
	}
	   
  }
}

void Double_Down(void)
{
  uchar i,j;
  for(j=0;j<8;j++)
  {	
  	for(i=0;i<8;i++)
	{
		while(1)
		{
			P7=eightCCW[i];
			P6=eightCW[i];
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
	if((pageFlag%2)== 0)
	{
		DrawcharS(" TimeN  :",0,1),DrawcharS(str_n,0,10);
		DrawcharS(" StepFre:",1,1),DrawcharS(str_f,1,10),DrawcharS("HZ",1,14);
		DrawcharS(" Speed  :",2,1),DrawcharS(str_s,2,10),DrawcharS("c/m",2,13);
		DrawcharS("6.Down",3,0);DrawcharS("7.Up",3,8);
		
	}
	else
	{
		DrawcharS("1.",0,0),DrawhanziS("0234",0,1);
		DrawcharS("2.",1,0),DrawhanziS("1234",1,1);
		DrawcharS("3.",2,0),DrawhanziS("4",2,1),DrawcharS("1/4",2,4),DrawhanziS("5",2,4);
		DrawcharS("4.",3,0),DrawhanziS("4",3,1),DrawcharS("1/8",3,4),DrawhanziS("5",3,4);
	}	
}

void Caculate()
{
	frequency = 10000/timeThreshold;
	speed = 146/timeThreshold;
	itoa(timeThreshold,str_n);
	itoa(frequency,str_f);
	itoa(speed,str_s);
	
}