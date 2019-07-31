#include "io430g2553.h"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  P1DIR |= BIT4; //����Ϊ�����ʽ
  P1SEL |= BIT4; //ʹ��P1.4�ڶ�����
  
  DCOCTL |= (BIT7); 
  DCOCTL &= ~(BIT5 + BIT6); 
  
  BCSCTL1 |= BIT0 + BIT1 + BIT2 + BIT3; //RSEL = 15;
  
  //ѡ��1��Ƶ���DCOCLK��ΪMCLK ѡ��1��Ƶ���DCOCLK��ΪSMCLK
  BCSCTL2 &= ~(BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
  
  while(1);

}

