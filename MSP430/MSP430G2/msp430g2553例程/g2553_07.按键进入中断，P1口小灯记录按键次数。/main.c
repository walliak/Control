#include<msp430g2553.h>

#define uint unsigned int

void delay(){ 
  uint i=10000; 
  while(i--); 
}

unsigned int num = 0;

void main(void){
  WDTCTL=WDTPW+WDTHOLD;
  P2DIR|=0xff; // P2 is output.
  P2OUT|=0x00; // P2 is output.
  P1DIR|=0x00; // P1 is input.
  P1OUT=0xff; // P1 pull Up.
  P1REN|=0xff; // Enable P1 pull Up.
  P1IE|=0x08;// P1.3 interrupt enabled
  P1IES|=0x08;// P1.3 Hi/lo edge
  P1IFG&=~0x08;// P1.3 IFG cleared

  _BIS_SR(LPM4_bits+GIE);//EnterLPM4
}

//Port1interruptserviceroutine

#pragma vector=PORT1_VECTOR

__interrupt void Port_1(void){
  if(num==0){P2OUT=0;num=1;}
  else{P2OUT=1;
    num=0;};
  
  
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