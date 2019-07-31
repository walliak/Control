#include <msp430g2553.h>

#include "key.h"



/***************    ��������    *****************
* VCC --- Һ����λ pin11

* PIN 2.0 -- A1 -- pin1
* PIN 2.1 -- A2 -- pin3
* PIN 2.2 -- A3 -- pin5
* PIN 2.3 -- B1 -- pin7
* PIN 2.4 -- B2 -- pin8
* PIN 2.5 -- B3 -- pin9             -- by akai --
************************************************/

/**********************************************************************************************************
* �������ƣ�KeyPort_Init
* �������ܣ�ʹ�ü���ǰ������õĳ�ʼ������
**********************************************************************************************************/
void KeyPort_Init ()
{
  P2DIR |= (BIT0 + BIT1 + BIT2); // PA 0,1,2 ���
  P2OUT &= ~(BIT0 + BIT1 + BIT2); // PA 0,1,2 ����͵�ƽ
  
  P2DIR &= ~(BIT3 + BIT4 + BIT5); // PB 0,1,2 ����
  P2REN |= (BIT3 + BIT4 + BIT5); // PB 0,1,2 ʹ��������
  P2OUT |= (BIT3 + BIT4 + BIT5); // PB 0,1,2 ����
}

/**********************************************************************************************************
* �������ƣ�KeyScan
* �������ܣ�����ɨ�裬����0��ʾ�޼����£�1-9����������
**********************************************************************************************************/
unsigned char KeyScan()
{
  unsigned long i; // �ڲ���������
  
  P2OUT &= ~(BIT0 + BIT1 + BIT2); // PA 0,1,2 ����͵�ƽ
  if( (0!=(P2IN & BIT3)) && (0!=( P2IN & BIT4 )) && (0!=( P2IN & BIT5)) ) // û�а���������0 
  {
    return 0;
  }
  else // �м����£���ʱ��
  {    
    for( i = 0 ; i < 1000 ; i ++ );  // �����ʱ����
    
    P2OUT &= ~(BIT0); // PA 1 ����͵�ƽ
    P2OUT |= (BIT1 + BIT2); // PA 2,3 ����ߵ�ƽ
  
    switch( P2IN & (BIT3 + BIT4 + BIT5) )
    {
    case 0x30:return 1;break;
    case 0x28:return 2;break;
    case 0x18:return 3;break;
    default:break;
    }
    
    P2OUT &= ~(BIT1); // PA 2 ����͵�ƽ
    P2OUT |= (BIT0 + BIT2); // PA 1,3 ����ߵ�ƽ
  
    switch( P2IN & (BIT3 + BIT4 + BIT5) )
    {
    case 0x30:return 4;break;
    case 0x28:return 5;break;
    case 0x18:return 6;break;
    default:break;
    }
    
    P2OUT &= ~(BIT2); // PA 3 ����͵�ƽ
    P2OUT |= (BIT0 + BIT1); // PA 1,2 ����ߵ�ƽ
  
    switch( P2IN & (BIT3 + BIT4 + BIT5) )
    {
    case 0x30:return 7;break;
    case 0x28:return 8;break;
    case 0x18:return 9;break;
    default:break;
    }
    
    return 0;
  }
} 
  