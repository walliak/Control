#include <msp430g2553.h>

#include "key.h"

/***************    ��������    *****************
* PIN 2.0 -- A1 -- pin1
* PIN 2.1 -- A2 -- pin3
* PIN 2.2 -- A3 -- pin5
* PIN 2.3 -- B1 -- pin7
* PIN 2.4 -- B2 -- pin8
* PIN 2.5 -- B3 -- pin9             -- by akai --
************************************************/

/***************  ��������˵��  *****************
* ͨ���޸����º궨�� ʵ��IO�ڵ�ͨ��
*                                   -- by akai --
************************************************/

// A1 ռ�� P2 �� �� BIT0 λ
#define PA1DIR          P2DIR
#define PA1REN          P2REN
#define PA1OUT          P2OUT
#define PA1IN           P2IN
#define BITA1           BIT0
// A2 ռ�� P2 �� �� BIT1 λ
#define PA2DIR          P2DIR
#define PA2REN          P2REN
#define PA2OUT          P2OUT
#define PA2IN           P2IN
#define BITA2           BIT1
// A3 ռ�� P2 �� �� BIT2 λ
#define PA3DIR          P2DIR
#define PA3REN          P2REN
#define PA3OUT          P2OUT
#define PA3IN           P2IN
#define BITA3           BIT2 

// B1 ռ�� P2 �� �� BIT3 λ
#define PB1DIR          P2DIR
#define PB1REN          P2REN
#define PB1OUT          P2OUT
#define PB1IN           P2IN
#define BITB1           BIT3
// B2 ռ�� P2 �� �� BIT4 λ
#define PB2DIR          P2DIR
#define PB2REN          P2REN
#define PB2OUT          P2OUT
#define PB2IN           P2IN
#define BITB2           BIT4
// B3 ռ�� P2 �� �� BIT5 λ
#define PB3DIR          P2DIR
#define PB3REN          P2REN
#define PB3OUT          P2OUT
#define PB3IN           P2IN
#define BITB3           BIT5

/**********************************************************************************************************
* �������ƣ�KeyPort_Init
* �������ܣ�ʹ�ü���ǰ������õĳ�ʼ������
**********************************************************************************************************/
void KeyPort_Init ()
{
  //**** P2DIR |= (BIT0 + BIT1 + BIT2); // PA 0,1,2 ���
  PA1DIR |= BITA1;
  PA2DIR |= BITA2;
  PA3DIR |= BITA3;
  
  //**** P2OUT &= ~(BIT0 + BIT1 + BIT2); // PA 0,1,2 ����͵�ƽ
  PA1OUT &= ~ BITA1;
  PA2OUT &= ~ BITA2;
  PA3OUT &= ~ BITA3;
    
  //**** P2DIR &= ~(BIT3 + BIT4 + BIT5); // PB 0,1,2 ����
  PB1DIR &= ~ BITB1;
  PB2DIR &= ~ BITB2;
  PB3DIR &= ~ BITB3;
  
  //**** P2REN |= (BIT3 + BIT4 + BIT5); // PB 0,1,2 ʹ��������
  PB1REN |= BITB1;
  PB2REN |= BITB2;
  PB3REN |= BITB3;
  
  //**** P2OUT |= (BIT3 + BIT4 + BIT5); // PB 0,1,2 ����
  PB1OUT |= BITB1;
  PB2OUT |= BITB2;
  PB3OUT |= BITB3;
}

/**********************************************************************************************************
* �������ƣ�KeyScan
* �������ܣ�����ɨ�裬����0��ʾ�޼����£�1-9����������
**********************************************************************************************************/
unsigned char KeyScan()
{
  unsigned long i; // �ڲ���������
  
  //**** P2OUT &= ~(BIT0 + BIT1 + BIT2); // PA 0,1,2 ����͵�ƽ
  PA1OUT &= ~BITA1;
  PA2OUT &= ~BITA2;
  PA3OUT &= ~BITA3;
  
  //**** if( (0!=(P2IN & BIT3)) && (0!=( P2IN & BIT4 )) && (0!=( P2IN & BIT5)) ) // û�а���������0 
  if ( (0!=(PB1IN & BITB1)) && (0!=( PB2IN & BITB2 )) && (0!=( PB3IN & BITB3)) )
  {
    return 0;
  }
  else // �м����£���ʱ��
  {    
    for( i = 0 ; i < 1000 ; i ++ );  // �����ʱ����
    
    //**** P2OUT &= ~(BIT0); // PA 1 ����͵�ƽ
    PA1OUT &= ~BITA1;
    //**** P2OUT |= (BIT1 + BIT2); // PA 2,3 ����ߵ�ƽ
    PA2OUT |= BITA2;
    PA3OUT |= BITA3;

    if( 0 == (PB1IN & BITB1) ) {return 1;}
    if( 0 == (PB2IN & BITB2) ) {return 2;}
    if( 0 == (PB3IN & BITB3) ) {return 3;}
    
    //**** P2OUT &= ~(BIT1); // PA 2 ����͵�ƽ
    PA2OUT &= ~BITA2;
    //**** P2OUT |= (BIT0 + BIT2); // PA 1,3 ����ߵ�ƽ
    PA1OUT |= BITA1;
    PA3OUT |= BITA3;

    if( 0 == (PB1IN & BITB1) ) {return 4;}
    if( 0 == (PB2IN & BITB2) ) {return 5;}
    if( 0 == (PB3IN & BITB3) ) {return 6;}
    
    //**** P2OUT &= ~(BIT2); // PA 3 ����͵�ƽ
    PA3OUT &= ~BITA3;
    //**** P2OUT |= (BIT0 + BIT1); // PA 1,2 ����ߵ�ƽ
    PA1OUT |= BITA1;
    PA2OUT |= BITA2;

    if( 0 == (PB1IN & BITB1) ) {return 7;}
    if( 0 == (PB2IN & BITB2) ) {return 8;}
    if( 0 == (PB3IN & BITB3) ) {return 9;}
    
    return 0;
  }
} 
  