#include "msp430G2553.h"
#include "stdio.h"
#include "uart.h"


/***************    ���ڽӷ�    *****************
* RXD --- g2553 P1.1
* TXD --- g2553 P1.2
************************************************/

#define BUFSIZE 10
char a[BUFSIZE];
int length = 0;
int b = 0;


void Init_uart0()
{

  UCA0CTL1|=UCSWRST;//�����λ����ʹ��
  UCA0CTL0&=~UC7BIT;//�ַ�����Ϊ8
  UCA0CTL1|=UCSSEL_2;//ѡ��ϵͳʱ��
  UCA0BR0=0x6D;  //������Ϊ9600
  UCA0BR1=0;
  UCA0MCTL=0;//UCA0MCTL=UCBRS0;
  IE2=UCA0RXIE+UCA0TXIE;//������ʹ��
  UCA0CTL1&=~UCSWRST;
  P1SEL|=BIT1+BIT2; //��P1.1 P1.2��Ϊ�ڶ�����
  P1SEL2|=BIT1+BIT2;
  IE2 |= UCA0RXIE ;
}

//����ʵ��printf�е�putchar
int putchar(int s)
{
    UCA0TXBUF=s;
    while((IFG2&UCA0TXIFG)==0); //��ѯ�����Ƿ����
    IFG2&=~UCA0TXIFG; //�������һ��־λ
    return s;
    
}
��
void clear(void)
{
  length=0;    
  memset(a,'\0',BUFSIZE);
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void usart0_rx(void)
{
  IFG2 &=~UCA0RXIFG; //clear RX interrupt flag
  a[length]=UCA0RXBUF;
  length++;
  P1OUT^=0x01;//
}

void Uart0Sends(char *s)
{
  while(*s != '\0')
  {
    UCA0TXBUF = *s;
    while((IFG2 & UCA0TXIFG) == 0); //��ѯ�����Ƿ����
    IFG2 &= ~UCA0TXIFG; //�������һ��־λ
    s++;
  }
}