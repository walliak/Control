#include "msp430G2553.h"
#include "stdio.h"

#include "uart.h"

/***************    串口接法    *****************
* RXD --- g2553 P1.1
* TXD --- g2553 P1.2
************************************************/

int a[8],i;

void Init_uart0()
{
  UCA0CTL1 |= UCSWRST;
  UCA0CTL0 &= ~UC7BIT;//字符长度为8
  UCA0CTL1 |= UCSSEL_2;//选择系统时钟
  UCA0BR0 = 0x6D;  //波特率为9600
  UCA0BR1 = 0;
  UCA0MCTL = 0;//UCA0MCTL=UCBRS0;
  IE2 = UCA0RXIE + UCA0TXIE;//开接收使能
  UCA0CTL1 &= ~UCSWRST;
  P1SEL |= BIT1 + BIT2; //将P1.1 P1.2设为第二功能
  P1SEL2 |= BIT1 + BIT2;
}


void Uart0Sends(char *s)
{
  while(*s != '\0')
  {
    UCA0TXBUF = *s;
    while((IFG2 & UCA0TXIFG) == 0); //查询发送是否结束
    IFG2 &= ~UCA0TXIFG; //清除发送一标志位
    s++;
  }
}

int putchar(int c)
{
  UCA0TXBUF = c;
  while((IFG2&UCA0TXIFG) == 0); //查询发送是否结束
  IFG2 &= ~UCA0TXIFG; //清除发送一标志位
  
  return c;
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void usart0_rx(void)
{
  while((IFG2&UCA0RXIFG )==0);
  i=UCA0RXBUF;
}
