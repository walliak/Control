#include<msp430g2553.h>

#include "lcd.h"
#include "key.h"

/***************    电源接法    *****************
* VCC --- 液晶复位 pin11
* VCC --- 液晶电源 pin2
* GND --- 液晶电源 pin4
************************************************/

unsigned int num;

void main(void){
  
  WDTCTL=WDTPW+WDTHOLD;
  
  LCD_init();
  KeyPort_Init();
  
  LCD_drawStrAt("Hello Key & Lcd!",16,0,0);

  while(1)
  {
    num=KeyScan();
    switch(num)
    {
    case 1:LCD_clear();LCD_drawCharAt('1',1,1);break;
    case 2:LCD_clear();LCD_drawCharAt('2',1,1);break;
    case 3:LCD_clear();LCD_drawCharAt('3',1,1);break;
    case 4:LCD_clear();LCD_drawCharAt('4',1,1);break;
    case 5:LCD_clear();LCD_drawCharAt('5',1,1);break;
    case 6:LCD_clear();LCD_drawCharAt('6',1,1);
            num=100;while(num--){LCD_drawPoint(num,10);};
            break;
    case 7:LCD_clear();LCD_drawCharAt('7',1,1);
            LCD_drawChar('A');break;
    case 8:LCD_clear();LCD_drawCharAt('8',1,1);
            LCD_drawStr("123456789",5);break;
    case 9:LCD_clear();LCD_drawCharAt('9',1,1);
            LCD_drawStrAt("Hello Key & Lcd!",16,0,2);
            LCD_drawStrAt("Hello Key & Lcd!",16,0,3);
            LCD_clearLine(2);
            break;
    default: break;
    }
  }
  
}
