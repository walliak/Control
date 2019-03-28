/////////////////////////////////////
//  Generated Initialization File  //
/////////////////////////////////////

#include "C8051F020.h"
#include "lcd.h"
#include "key.h"
#include "adc.h"
#include "math.h"
#include "String.h"

unsigned char str[20];
void itoa(int n, char *s);
void reverse(char *s);
void CompositeChars(char hour,char minute,char second,char*setTime);

// Peripheral specific initialization functions,
// Called from the Init_Device() function
void Reset_Sources_Init()
{
    WDTCN     = 0xDE;
    WDTCN     = 0xAD;
    RSTSRC    = 0x04;
}

void Timer_Init()//定时器3计时1ms
{
    CKCON     = 0x20;
    TMR3CN    = 0x02;
    TMR3RLL   = 0xCD;
    TMR3RLH   = 0xD4;
}

void OpenTimer3()  //开定时器
{
	TMR3CN|=0x04;
}

void CloseTimer3() //关定时器
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
    // P0.0  -  Unassigned,  Open-Drain, Digital
    // P0.1  -  Unassigned,  Open-Drain, Digital
    // P0.2  -  Unassigned,  Open-Drain, Digital
    // P0.3  -  Unassigned,  Open-Drain, Digital
    // P0.4  -  Unassigned,  Open-Drain, Digital
    // P0.5  -  Unassigned,  Open-Drain, Digital
    // P0.6  -  Unassigned,  Open-Drain, Digital
    // P0.7  -  Unassigned,  Open-Drain, Digital

    // P1.0  -  Unassigned,  Open-Drain, Digital
    // P1.1  -  Unassigned,  Open-Drain, Digital
    // P1.2  -  Unassigned,  Open-Drain, Digital
    // P1.3  -  Unassigned,  Open-Drain, Digital
    // P1.4  -  Unassigned,  Open-Drain, Digital
    // P1.5  -  Unassigned,  Open-Drain, Digital
    // P1.6  -  Unassigned,  Open-Drain, Digital
    // P1.7  -  Unassigned,  Open-Drain, Digital

    // P2.0  -  Unassigned,  Open-Drain, Digital
    // P2.1  -  Unassigned,  Open-Drain, Digital
    // P2.2  -  Unassigned,  Open-Drain, Digital
    // P2.3  -  Unassigned,  Open-Drain, Digital
    // P2.4  -  Unassigned,  Open-Drain, Digital
    // P2.5  -  Unassigned,  Open-Drain, Digital
    // P2.6  -  Unassigned,  Open-Drain, Digital
    // P2.7  -  Unassigned,  Open-Drain, Digital

    // P3.0  -  Unassigned,  Open-Drain, Digital
    // P3.1  -  Unassigned,  Open-Drain, Digital
    // P3.2  -  Unassigned,  Open-Drain, Digital
    // P3.3  -  Unassigned,  Open-Drain, Digital
    // P3.4  -  Unassigned,  Push-Pull,  Digital
    // P3.5  -  Unassigned,  Push-Pull,  Digital
    // P3.6  -  Unassigned,  Open-Drain, Digital
    // P3.7  -  Unassigned,  Open-Drain, Digital

    P3MDOUT   = 0x30;
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
    IE        = 0x80;//打开总的中断
    EIE2      = 0x01;//打开定时器3的中断
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

 	 unsigned char key=0,flag=0;	 
	 unsigned char hour=0,minute=0,second=0;
	 unsigned char nowHour=0,nowMinute=0,nowSecond=0;
	 unsigned char setTime[10]="SetTime ";
	 unsigned char nowTime[10]="NowTime ";
	 unsigned int totalTime,i=0;

	 Init_Device();
	 newLCDInit();

	 Clear();
     DrawcharS("Project-2",1,4);
     DrawcharS("3.14--3.21",2,4);        
	 for(i=0;i<255;i++)
	 	{
			Delayms(100);
		}
	 Clear();			  	


	 while(1)
	 {	 		   
	   CompositeChars(hour,minute,second,setTime);
	   DrawcharS(str,0,0);	   
       key = KeyScan();
	   if(key != 0)
		{
			switch(key)
			{	case 1: hour++;
						Clear();
						break;
				case 6:	if(hour>0) 
						hour--;
						Clear();
						break;
				case 2: minute++;
						Clear();
						break;
				case 7:	if(minute>0)
						minute--;
						Clear();
						break;
				case 3: second++;
						Clear();
						break;
				case 8: if(second>0)
						second--;
						Clear();
						break;
				case 9: flag=1;	  				//开始计时，恢复计时
						OpenTimer3();
						Clear();
						break;
				case 4: CloseTimer3();			//暂停计时
						Clear();
						break;
				case 5: ms=0;	   				//重新开始计时
						sTotal=0;
						OpenTimer3();
						Clear();
						break;
			}
		}
		totalTime=3600*hour+60*minute+second;
		if(flag>0)
	 		{	
				P5|=0x02;			
				nowHour=sTotal/3600; nowMinute=(sTotal%3600)/60; nowSecond=(sTotal%3600)%60;
				CompositeChars(nowHour,nowMinute,nowSecond,nowTime);
	 			DrawcharS(str,1,0);
				str[0]='\0';				
				if(sTotal>=totalTime)
				{
					DrawcharS("Time is up!",3,0);
					CloseTimer3();
					P5&=~0x02;						//P5.2置为低电平，灯亮。
				}
			}		
	 }
}



void itoa(int n, char *s)
{
  int sign;
  char *t = s;  
  if ((sign = n) < 0)
    n = -n; 
  do
  {
    *s++ = n % 10 + '0';
  } 
  while ((n /= 10) >0); 
  if (sign < 0)
    *s++ = '-'; 
  *s = '\0';  
  reverse(t);
}

 void reverse(char *s)
{
  int c;
  char *t; 
  for (t = s + (strlen(s) - 1); s < t; s++, t-- )
  {
    c = *s;
    *s = *t;
    *t = c;
  }
}

	


void CompositeChars(char hour,char minute,char second,char*setTime)
{
		
	unsigned char S_hour[4],S_minute[4],S_second[4],temp[4];
	unsigned char i;
	if(hour>9)	
		itoa(hour,S_hour);	
	else
	{	
		itoa(hour,S_hour);	
		strcpy(temp,S_hour);
		strcpy(S_hour,"0");
		strcat(S_hour,temp);
		
	}

	if(minute>9)	
		itoa(minute,S_minute);	
	else
	{	
		itoa(minute,S_minute);	
		strcpy(temp,S_minute);
		strcpy(S_minute,"0");
		strcat(S_minute,temp);
		
	}
	if(second>9)	
		itoa(second,S_second);	
	else
	{	
		itoa(second,S_second);	
		strcpy(temp,S_second);
		strcpy(S_second,"0");
		strcat(S_second,temp);		
	}

	strcpy(str,setTime);
	strcat(str,S_hour);
	strcat(str,":");
	strcat(str,S_minute);
	strcat(str,":");
	strcat(str,S_second);

	for(i=0;str[i]!='\0';i++)
	{
		if(str[i]=='s')
		{
			i++;
			str[i]='\0';
			break;
		}
	}
	
} 
