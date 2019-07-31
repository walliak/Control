#include<msp430g2553.h>

#define uint unsigned int

unsigned int count = 10;

void delay(){ 
  uint i=10; 
  while(i--); 
  WDTCTL=WDTPW+WDTCNTCL;
}

void main(void){
  
  //WDTCTL=WDTPW+WDTHOLD;//stop the dog!!!
  WDTCTL=WDTPW+WDTSSEL+WDTIS1;
  P1DIR|=0x01; // P1.0 is output, P1.1-P1.7 is input.
  P1OUT=0x08; // P1.3 pull Up.
  P1REN|=0x08; // Enable P1.3 pull Up.
    
  while(count--) { 
    P1OUT ^=BIT0; 
    delay(); 
  }
  
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

