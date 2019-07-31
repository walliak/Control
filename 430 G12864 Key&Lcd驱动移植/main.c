
#include "io430.h"
#include "430_key.h"
#include "430_lcd.h"

unsigned char B_Rotation[8]={0x01,0x09,0x08,0x0c,0x04,0x06,0x02,0x03};//反转表格
unsigned char F_Rotation[8]={0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};//正转表格
unsigned  int sintab[100]={2048 ,2178 ,2307 ,2436 ,2562 ,2687 ,2809 ,2928 ,3044 ,3155 ,3262 ,3364 ,3461 ,3552 ,3638 ,3716 ,3788 ,3853 ,3911 ,3961 ,4004 ,4038 ,4065 ,4083 ,4094 ,4095 ,4090 ,4075 ,4053 ,4022 ,3983 ,3937 ,3883 ,3822 ,3753 ,3678 ,3596 ,3508 ,3414 ,3314 ,3209 ,3100 ,2986 ,2869 ,2748 ,2625 ,2499 ,2372 ,2243 ,2113 ,1983 ,1853 ,1724 ,1597 ,1471 ,1348 ,1227 ,1110 ,996 ,887 ,782 ,682 ,588 ,500 ,418 ,343 ,274 ,213 ,159 ,113 ,74 ,43 ,21 ,6 ,0 ,2 ,13 ,31 ,58 ,92 ,135 ,185 ,243 ,308 ,380 ,458 ,544 ,635 ,732 ,834 ,941 ,1052 ,1168 ,1287 ,1409 ,1534 ,1660 ,1789 ,1918 ,2048 };

void delay(int ms)
{
  int i = 0,j=0;
  for(;i<500;i++)
  {
    for(j = 0;j<ms;j++)
    {
 //     _NOP();
    }
  }
}

void SetVcoreUp (unsigned int level)
 {
     // Open PMM registers for write
     PMMCTL0_H = PMMPW_H;
     // Set SVS/SVM high side new level
     SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
     // Set SVM low side to new level
     SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
     // Wait till SVM is settled
     while ((PMMIFG & SVSMLDLYIFG) == 0);
    // Clear already set flags
     PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
     // Set VCore to new level
     PMMCTL0_L = PMMCOREV0 * level;
     // Wait till new level reached
     if ((PMMIFG & SVMLIFG))
     while ((PMMIFG & SVMLVLRIFG) == 0);
     // Set SVS/SVM low side to new level
     SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
     // Lock PMM registers for write access
     PMMCTL0_H = 0x00;
 }


void MCLK_Init() //系统时钟配置
{
    WDTCTL = WDTPW+WDTHOLD;

    P7SEL |= BIT7; //MCLK
    P7DIR |= BIT7;
    P5SEL |= BIT4|BIT5;
      
    UCSCTL6 |= XCAP_3;
    UCSCTL6 &= ~XT1OFF;//打开 XT1，否则 XT1LFOFFG 可能报错
    
    SetVcoreUp(3); //提高 Vcore 电压到最高级，以满足倍频需求该函数位于HAL_PMM.H 中
    __bis_SR_register(SCG0);//该语法为固定格式，意为将括号内的变量置位，SCG0与系统工作模式有关，此时 MCLK 暂停工作
    
    UCSCTL0 = 0; //先清零，FLL 运行时，该寄存器系统会自动配置，不用管
    UCSCTL1 = DCORSEL_5;
    UCSCTL2 = FLLD_1 | 152;//FLLD=1,FLLN=380,则频率为2*（380+1）*32.768=24.969MHZ
    
    __bic_SR_register(SCG0);
    __delay_cycles(782000);//系统自带的精确延时，单位 us
    while(SFRIFG1 & OFIFG) 
    {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
        SFRIFG1 &= ~OFIFG;
    }
    UCSCTL4 = UCSCTL4&(~(SELS_7|SELM_7))|SELS_3|SELM_3;
}
void ShowSin()  //画正弦函数
{
	int x,y;
	for(x=0;x<128;x++)				   
	{
		DrawPoint(x,31);	
	}
	for(y=0;y<64;y++)				   
	{
		DrawPoint(63,y);	
	}
	for(x=0;x<128;x++)				 
	{
		y = (sintab[x%100])/64;
		if(x != 63 && y != 31)
		{
			if(y > 23 && y < 31)
				DrawPoint(x,31);
			DrawPoint(x,y);
		}
	} 
		
}

int main( void )
{
    WDTCTL=WDTPW+WDTHOLD; //关闭看门狗
    KeyPort_Init();
    newLCDInit();
    MCLK_Init();
    P6DIR = 0xff;//配置P6引脚输出模式
    P1DIR = 0xff;//配置P1引脚输出模式
    //P1OUT = 0x01;//P1.0灯亮
    int i,j;  
    Clear();
    LCDWrite(W_CMD,0xA7);	  //反显命令
    DrawcharS("00:00:00",1,4);
    delay(2000);         
    Clear();	  
    for(i = 0; i < 3; i++)	  //显示文字		
        Drawchinese(i,1,i);
    delay(2000); 
    Clear();
    LCDWrite(W_CMD,0xA6);	  //正常显命令
    for(i = 0; i < 3; i++)	  //显示文字		
        Drawchinese(i,1,5+2*i);           
     delay(2000);     
	 
    Clear();			  //清屏
           
    ShowSin();
    delay(2000); 
    Clear();         
  while(1)
  {
    unsigned char key  = 0;
    key = KeyScan();
    if(key != 0)
    {
      switch(key)
      {
        case 1:     //P1.0灯亮
          P1OUT = 0x01;
          break;
        case 4:     //P1.0灯灭
          P1OUT = 0x00;
          break;
        case 7:
            P1OUT ^= 0x01;//P1.0反转
          break;
        case 9:    //电机转
          for(i = 0;i<523;i++)
          {
            for(j = 0;j<8;j++)
            {
              P6OUT = F_Rotation[j];                                                                                                                                            
              delay(12);
            }
          }
          break;
      }
    }
    
    
  }

}
