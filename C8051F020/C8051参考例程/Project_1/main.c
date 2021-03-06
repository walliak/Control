/////////////////////////////////////
//  Generated Initialization File  //
/////////////////////////////////////

#include "C8051F020.h"
#include "lcd.h"
#include "key.h"
#include "adc.h"
#include "math.h"

// Peripheral specific initialization functions,
// Called from the Init_Device() function
void Reset_Sources_Init()
{
    WDTCN     = 0xDE;
    WDTCN     = 0xAD;
    RSTSRC    = 0x04;
}

void Timer_Init()
{
    CKCON     = 0x20;
    TMR3CN    = 0x06;
    TMR3RLL   = 0xA0;
    TMR3RLH   = 0xFF;
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
    IE        = 0x80;
    EIE2      = 0x03;
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
	 unsigned int i,y;
	 Init_Device();
     for(i=0;i<1000;i++)
	 adcmem[i]=0;
	 newLCDInit();
	 Clear();
	 LCDWrite(W_CMD,0xA7);	  //��������  
     DrawcharS("Project-1",1,4);
     DrawcharS("3.7--3.14",2,4);        
	 for(i=0;i<255;i++)
	 	{
			Delayms(100);
		}
	 LCDWrite(W_CMD,0xA6);	  //����������           
	 Clear();			  	  //����


	 while(1)
	 {

	   DrawcharS("press the button",1,0);
	   DrawcharS("----------------",2,0);
       key = KeyScan();
		if(key != 0)
		{
			switch(key)
			{
				//��ʾ����
			   case 1:	Clear();flag=0;
			   			while(1){
							DrawcharS("0123456789",0,0);
							 
							flag=keyScan();
							if(flag==9)
							break;
						}
			            Clear();
						break;
				//��ʾ��ĸ
			   case 2:  Clear();flag=0;
			   			while(1){
							DrawcharS("abcdefghijklmnopqrstuvwxyz",0,0); 
							flag=keyScan();
							if(flag==9)
							break;
						}
			            Clear();
						break;
				//��ʾ������
			   case 3:	Clear();flag=0;
			   			while(1){
							for(i=0;i<64;i++)
						    DrawPoint(i,i);
				            for(i=64;i<127;i++)
						    DrawPoint(i,127-i);
							flag=keyScan();
							if(flag==9)
							break;
						}
			            Clear();
						break;
				//��ʾ���Ҳ�
			   case 4:  Clear();flag=0;
			   			while(1){
							for(i=0;i<128;i++)
							DrawPoint(i,(sintab[i%100])>>6);
							flag=keyScan();
							if(flag==9)
							break;
						}
					    Clear();
						break;
				//��ʾʮ��
			   case 5:	Clear();flag=0;
			   			while(1){
							for(i=0;i<127;i++)		
							DrawPoint(i,31);
			    		    for(i=0;i<64;i++)						
							DrawPoint(63,i);						
							flag=keyScan();
							if(flag==9)
							break;
						}
						Clear();
						break;
				case 6:	Clear();flag=0;
			   			while(1){
							DrawhanziS("0123456",1,0);
							DrawhanziS("0123456",2,0);
							flag=keyScan();
							if(flag==9)
							break;
						}
						Clear();
						break;
				case 7: Clear();flag=0;
						while(1)
						{
							for(i=0;i<120;i++)
							DrawPoint(i,15);
							for(i=0;i<56;i++)
							DrawPoint(15,i);
							for(i=32;i<120;i++)
							{
								y=(i-32)/2+16;
								DrawPoint(i,y);
							}
							DrawcharS("y",0,2);
							DrawcharS("x",2,15);
							DrawcharS("o",2,2);

							flag=keyScan();
							if(flag==9)
							break;
						}
						Clear();
						break;
				//Ĭ�Ϸ���
			   default:  break;
			}
		 key=0;
	    }
	 }
}
