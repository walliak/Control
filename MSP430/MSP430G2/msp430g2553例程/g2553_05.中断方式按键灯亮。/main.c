#include<msp430g2553.h>

#define uint unsigned int

void delay(){ 
  uint i=10000; 
  while(i--); 
}

void main(void){
  WDTCTL=WDTPW+WDTHOLD;
  P1DIR|=0x01; // P1.0 is output, P1.1-P1.7 is input.
  P1OUT=0x08; // P1.3 pull Up.
  P1REN|=0x08; // Enable P1.3 pull Up.
  P1IE|=0x08;// P1.3 interrupt enabled
  P1IES|=0x08;// P1.3 Hi/lo edge
  P1IFG&=~0x08;// P1.3 IFG cleared

  _BIS_SR(LPM4_bits+GIE);//EnterLPM4
}

//Port1interruptserviceroutine

#pragma vector=PORT1_VECTOR

__interrupt void Port_1(void){
  P1OUT^=0x01;//
  
  delay();
  while(1){
    if(P1IN&BIT3){
      delay();
      break;
    }
    else{}
  }
      
  P1IFG&=~0x08;//P1.3IFGcleared
}