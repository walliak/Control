#include<msp430g2553.h>

#include "lcd.h"
#include "key.h"
#include "uart.h"
#include "stdio.h"

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
  
  LCD_init();
  KeyPort_Init();
  Init_uart0();
  _EINT();
  
  LCD_drawStrAt("Hello Key & Lcd!",16,0,0);

  while(1)
  {
    num=KeyScan();
    switch(num)
    {
    case 1:LCD_clear();printf("key press num - 1\n");LCD_drawCharAt('1',1,1);break;
    case 2:LCD_clear();printf("key press num - 2\n");LCD_drawCharAt('2',1,1);break;
    case 3:LCD_clear();printf("key press num - 3\n");LCD_drawCharAt('3',1,1);break;
    case 4:LCD_clear();printf("key press num - 4\n");LCD_drawCharAt('4',1,1);break;
    case 5:LCD_clear();printf("key press num - 5\n");LCD_drawCharAt('5',1,1);break;
    case 6:LCD_clear();printf("key press num - 6\n");LCD_drawCharAt('6',1,1);break;
    case 7:LCD_clear();printf("key press num - 7\n");LCD_drawCharAt('7',1,1);break;
    case 8:LCD_clear();printf("key press num - 8\n");LCD_drawCharAt('8',1,1);break;
    case 9:LCD_clear();printf("key press num - 9\n");LCD_drawCharAt('9',1,1);break;
    default: break;
    }
  }

}
