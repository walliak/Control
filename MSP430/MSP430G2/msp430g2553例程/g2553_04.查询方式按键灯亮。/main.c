
#include "io430.h"

void main(void) { 
  WDTCTL = WDTPW + WDTHOLD; 
  
 
  
  P1DIR |= BIT0;
  
  P1REN |= BIT5;
  P1OUT |= BIT5;
  
  P1REN |= BIT3; // in port
  P1OUT |= BIT3; // up pull
  while(1)
  {
//    if(P1IN&BIT3)
//      P1OUT|=BIT0;
//    else
//      P1OUT&=~BIT0;
    if(P1IN&BIT3)
        P1OUT|=BIT0;
    else
      P1OUT&=~BIT0;
  }  
}

