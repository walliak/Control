/////////////////////////////////////
//  Generated Initialization File  //
/////////////////////////////////////

#include "C8051F020.h"
#include "key.h"
#include "Timer3.h"
#include "math.h"
#include "lcd.h"
#include "compositechars.h"

#define SetBit(x,y) x|=(1<<y)
#define ClrBit(x,y)	x&=~(1<<y)
#define ReverseBit(x,y) x^=(1<<y)
#define GetBit(x,y)	 ((x)>>(y)&1)
// Peripheral specific initialization functions,
// Called from the Init_Device() function
void DelayOneSecond(void);

void Reset_Sources_Init()
{
    WDTCN     = 0xDE;
    WDTCN     = 0xAD;
    RSTSRC    = 0x04;
}

void Timer_Init()//��ʱ��3��ʱ1ms
{
    CKCON     = 0x20;
    TMR3CN    = 0x02;
    TMR3RLL   = 0xCD;
    TMR3RLH   = 0xD4;
}

void OpenTimer3()  //����ʱ��
{
	TMR3CN|=0x04;
}

void CloseTimer3() //�ض�ʱ��
{
	TMR3CN&=~0X04;
}
void ADC_Init()
{
    ADC0CN    = 0x84;
}

void DAC_Init()
{
    DAC0CN    = 0x88;
    DAC1CN    = 0x80;
}

void Voltage_Reference_Init()
{
    REF0CN    = 0x03;
}

void Port_IO_Init()
{
    
	/*
	λ 7-0�� P3.[7:0]���˿� 3 ���������λ��   
	��д �� ��������� I/O ���ţ����� XBR0��XBR1 �� XBR2 �Ĵ��������ã� 
	0���߼��͵�ƽ����� 1���߼��ߵ�ƽ�����
	������Ӧ�� P3MDOUT.n λ = 0����Ϊ©����·���� 
	�������� XBR0��XBR1 �� XBR2 �Ĵ����������޹أ� 
	0��P3.n Ϊ�߼��͵�ƽ�� 1��P3.n Ϊ�߼��ߵ�ƽ��
	*/
    P3MDOUT   = 0x30;							
	
	/*
	UART1E��UART1 I/O ʹ��λ   
	0��UART1 I/O �������˿����š� 
	1��UART1 TX �� RX ���������˿����š�
	*/	
    XBR2      = 0x40;							 
}

void Oscillator_Init()
{
    int i = 0;
    OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    OSCICN    = 0x08;
}

void Interrupts_Init() 				
{									
    IE        = 0x80;//���ܵ��ж�
    EIE2      = 0x01;//�򿪶�ʱ��3���ж�
}

// Initialization function for device,
// Call Init_Device() from your main program
void Init_Device(void)
{
    Reset_Sources_Init();
    Timer_Init();
    ADC_Init();
    DAC_Init();
    Voltage_Reference_Init();
    Port_IO_Init();
    Oscillator_Init();
    Interrupts_Init();
}


main()
{	
	 unsigned char key=0,flag=0,y,m=0;
	 unsigned char nowHour=0,nowMinute=0,nowSecond=0;
	 unsigned char str[20];
	 unsigned char nowTime[10]="NowTime ";
	 unsigned int i,totalTime=0;

 	 //��ʼ��
	 Init_Device();
	 newLCDInit();

	 //������ʾ
	 Clear();
     DrawcharS("Project-3",1,4);
     DrawcharS("3.21--3.28",2,4);        
	 for(i=0;i<255;i++)
	 {
			Delayms(100);
	 }
	 Clear();			  	


	 while(1)
	 {
	 	
	 	DrawcharS("Press the button",1,0);
		P6=0xFF;
		P7=0xFF;
	 	key=KeyScan();
		if(key!=0)
		{
		 	switch(key)
			{
			 	case 1:	//�����ʱ��ȫ����ȫ��
						Clear(); //���� 
						
						while(1)
						{
							DrawcharS("Light up (1)",1,0);
							DelayOneSecond();
 							P6^=0xFF;
							P7^=0xFF;
							flag=KeyScan();
							if(flag==9)
							break;							
						}
						flag=0;
						Clear();
						break;
				case 2:	//�����ʱ,���ε���
						Clear();
						
						while(1)
						{	
							DrawcharS("Light up (2) ",1,0);
							for(y=0;y<16;y++)	 //0-16��Ҫȡ
							{
								flag=KeyScan();
								if(flag==9)
								{	
									m=1;
									break;
								}
							
								if(y<8)
									ClrBit(P6,y);
								else
									ClrBit(P7,y-8);
									DelayOneSecond();
							}
							P6=0xFF;
							P7=0xFF;
							if(m==1)
							{	
								m=0;
								break;
							}
													
						}
						flag=0;
						Clear();
						break;
				case 3:	//�����ʱ��P6.0->P6.7,P7.7->P7.0 ���Ƶ�������ѭ���ƶ�
						Clear();
						while(1)
						{
							DrawcharS("Light up (3)",1,0);
							
							for(y=0;y<16;y++)
							{  	
								flag=KeyScan();
								if(flag==9)
								{	
									m=1;
									break;
								}

								//д�����߼�
								i=(0x8000>>y)|(0x0001<<y);
								P7=~(i/256);
								P6=~(i%256);
								//

								DelayOneSecond();
							}

							P6=0xFF;
							P7=0xFF;
							if(m==1)
							{	
								m=0;
								break;
							}							
						}
						flag=0;
						Clear();
						break;
				case 4:	//�����ʱ��P6.0->P6.7,P7.7->P7.0 ���Ƶ�������ѭ���ƶ����ƶ����ʲ�ͬ��
						Clear();
						while(1)
						{
							DrawcharS("Light up (4)",1,0);
							for(y=0;y<32;y++)
							{
								flag=KeyScan();
								if(flag==9)
								{	
									m=1;
									break;
								}
															
								//д�����߼�
								i=(0x8000>>y%16)|(0x0001<<(y/2));
								P7=~(i/256);
								P6=~(i%256);
								//

								DelayOneSecond();
							}

							P6=0xFF;
							P7=0xFF;
							if(m==1)
							{	
								m=0;
								break;
							}							
						}
						flag=0;
						Clear();
						break;
				case 5:	//�����ʱ����
						Clear();
						while(1)
						{
							nowHour=totalTime/3600; nowMinute=(totalTime%3600)/60; nowSecond=(totalTime%3600)%60;
							CompositeChars(nowHour,nowMinute,nowSecond,nowTime,str);
	 						DrawcharS(str,1,0);
							DelayOneSecond();
 							totalTime++;
							
							flag=KeyScan();
							if(flag==9)
							break;							
						}
						flag=0;
						Clear();
						break;	
				case 6://��ʱ����ʱ�����ε���
						Clear();
						OpenTimer3();
						sTotal=0;
						while(1)
						{
							y=sTotal%17;
						  	DrawcharS("Light up (1-1)",1,0);
							if(y<8)
									ClrBit(P6,y);
							if(8<=y<16)
									ClrBit(P7,y-8);
							if(y==16)
								{	
									P6=0xFF;
									P7=0xFF;
								}						
							flag=KeyScan();
							if(flag==9)
							break;
						}
						flag=0;
						Clear();
						break;
				case 7:	//�����ʱ��P6.0->P6.7,P7.7->P7.0�������ε������������ʲ�ͬ
						Clear();
						while(1)
						{
							DrawcharS("Light up (7)",1,0);
							for(y=0;y<16;y++)
							{
								flag=KeyScan();
								if(flag==9)
								{	
									m=1;
									break;
								}
															
								if(y==8)
								{	
									P6=0xFF;
									ClrBit(P6,y%8);
								}
								ClrBit(P6,y%8);
								if(y%2==0)
								ClrBit(P7,7-y/2);

								DelayOneSecond();
							}

							P6=0xFF;
							P7=0xFF;
							if(m==1)
							{	
								m=0;
								break;
							}							
						}
						flag=0;
						Clear();
						break;
				default: break;
			
			
			}

		
		
		}
	 } 		   
	   
}

void DelayOneSecond(void)//��ʱ1s
{
 unsigned long a;
 for(a=0;a<153600;a++);

}

