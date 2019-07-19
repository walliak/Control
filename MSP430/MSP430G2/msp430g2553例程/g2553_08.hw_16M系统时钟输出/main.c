#include "io430g2553.h"

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  
  P1DIR |= BIT4; //配置为输出方式
  P1SEL |= BIT4; //使用P1.4第二功能
  
  DCOCTL |= (BIT7); 
  DCOCTL &= ~(BIT5 + BIT6); 
  
  BCSCTL1 |= BIT0 + BIT1 + BIT2 + BIT3; //RSEL = 15;
  
  //选择1分频后的DCOCLK作为MCLK 选择1分频后的DCOCLK作为SMCLK
  BCSCTL2 &= ~(BIT1 + BIT2 + BIT3 + BIT4 + BIT5 + BIT6 + BIT7);
  
  while(1);

}

