
#include "io430.h"
#define uint unsigned int

void delay(){ 
  uint i=10000; 
  while(i--); 
}

void main(void) { 
  WDTCTL = WDTPW + WDTHOLD; 
  P1DIR |=BIT0;
  while(1) { 
    P1OUT ^=BIT0; 
    delay(); 
  }
}

