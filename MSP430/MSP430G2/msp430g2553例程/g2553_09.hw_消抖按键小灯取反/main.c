#include "io430.h"

#define uint unsigned int

void delay(){ 
  uint i=10000; 
  while(i--); 
}

void main(void) { 
  WDTCTL = WDTPW + WDTHOLD; 
  P1DIR |= BIT0;
  P1DIR &= ~BIT3;// P1.3 is out
  P1REN = BIT3; // enable P1.3 UP PULL R
  P1OUT = BIT3; // set "up pull"
  while(1)
  {
    if(P1IN&BIT3){}
    else{
      P1OUT ^= BIT0; 
      delay();
      while(1){
        if(P1IN&BIT3){
          delay();
          break;
        }
        else{}
      }
    }
  }  
}

