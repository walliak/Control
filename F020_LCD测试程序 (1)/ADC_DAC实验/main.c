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

 	 unsigned char key=0,x=0,y=0;
	 unsigned int i=0,j=0;
	 Init_Device();
     for(i=0;i<1000;i++)
	 adcmem[i]=0;
	 newLCDInit();
	 Clear();
	 LCDWrite(W_CMD,0xA7);	  //反显命令  
     DrawcharS("Welcome",1,4);
     DrawcharS("to PHY!",2,4);
         
	 for(i=0;i<255;i++)
	 	{
			Delayms(100);
		}
//	 Clear();
	 LCDWrite(W_CMD,0xA6);	  //正常显命令           
//     DrawcharS("Welcome",1,4);
//     DrawcharS("to PHY!",2,4);
         
	 for(i=0;i<255;i++)
	 	{
			Delayms(100);
		}
	 Clear();			  //清屏
	for(i=0;i<128;i++)
		DrawPoint(i,(sintab[i%100])>>6);
	 for(i=0;i<255;i++)
	 	{
			Delayms(100);
		}
	 Clear();			  //清屏
	 while(1)
	 {
	   j++;	        
	   if(j>10000) {j=0;Clear();} 
   	   if(j<128){ DrawPoint(j,(adcmem[(j*20)%1000])>>6);}	   //在屏上显示波形
       key = KeyScan();
		if(key != 0)
		{
			switch(key)
			{
			   case 1:	Clear();
			   			for(x=0;x<128;x++)
			             {
							LCD_draw_point(x,0); // LCD左上角为原点哟！ X：0－127  Y：0－7 位置画点  一次一列八个点哟！ 
						 }   
						 break;
			   case 2:  Clear();
			   			for(x=0;x<128;x++)
			             {
							LCD_draw_point(x,1);
						 }   
						 break;
			   case 3:	Clear();
			   			for(x=0;x<128;x++)
			             {
							DrawPoint(x,0);	    // LCD左下角为坐标原点 x:0~127 y :0~63	  连续操作同一显示字节时,保留原始数据，画点！
						 }   
						 break;
			   case 4:  Clear();
			   			for(x=0;x<128;x++)
			             {
							DrawPoint(x,1);
						 }   
						 break;
			   case 5:	DrawPoint(63,0);		//画一个点
						break;
			   case 6:  LCD_draw_point(63,0);   //画八个点
						break;
			   case 7:	for(i=0;i<127;i++)		//画一十字，注意先后哟！
						{
							DrawPoint(i,31);
						}

		    		   for(i=0;i<64;i++)
						{
							DrawPoint(63,i);	
						}
						break;
			   case 8:  Clear();
			            DrawcharS("abcdefghijklmnopqrstuvwxyz",0,0);  //每行最多16个字符，多于16个换行！共4行，LCD左上角为原点哟！
			            P5&=(~0x01);	 //点亮LED
						break;
			   case 9:	Clear();
			            for(i=0;i<64;i++)
   					    DrawPoint(i,i);
			            for(i=64;i<127;i++)
   					    DrawPoint(i,127-i);
			            P5|=0x01;	 //灭LED
						break;
			}
		 x=0;
		 y=0;
		 key=0;

	    }
	 }
}
