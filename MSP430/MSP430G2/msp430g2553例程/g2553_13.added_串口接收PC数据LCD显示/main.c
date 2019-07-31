#include<msp430g2553.h>

#include "lcd.h"
#include "key.h"
#include "uart.h"
#include "stdio.h"

#define uint unsigned int
#define BUFSIZE 10
extern char a[BUFSIZE];
extern int length;
extern int b;

void delay(){ 
  uint i=10000; 
  while(i--); 
}
/***************    电源接法    *****************
* VCC --- 液晶复位 pin11
* VCC --- 液晶电源 pin2
* GND --- 液晶电源 pin4
************************************************/

unsigned int num;


void main(void){
  WDTCTL=WDTPW+WDTHOLD;
  
  BCSCTL1 = CALBC1_1MHZ;     
  DCOCTL  = CALDCO_1MHZ;
  Init_uart0();
    P1DIR|=0x01; // P1.0 is output, P1.1-P1.7 is input.
  P1OUT=0x08; // P1.3 pull Up.
  P1REN|=0x08; // Enable P1.3 pull Up.
  P1IE|=0x08;// P1.3 interrupt enabled
  P1IES|=0x08;// P1.3 Hi/lo edge
  P1IFG&=~0x08;// P1.3 IFG cleared

  _BIS_SR(LPM4_bits+GIE);//EnterLPM4
  _EINT();
  
  
  
  while(1)
  {
    if(length>0)
    {
      printf("%s\n",a); 
      clear();
    }

   
    //__delay_cycles (1048576);  
    

  }

}

#pragma vector=PORT1_VECTOR

__interrupt void Port_1(void){
 Uart0Sends("a");
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

