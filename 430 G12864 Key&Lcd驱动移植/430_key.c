/*2019��4��20�պ��Ľ���ֲ��G12864����KEYģ��*/
/*��ֲ�޸Ĳ��ֽ���ֻ��IO�ڵ����ú�ȥ���ٲ��ִ���*/
#include "io430.h"



void KeyPort_Init ()
{
   P3DIR |= 0x07 ; //P3.0-P3.2����Ϊ�������

   P3DIR &= ~0x70; //P3.4-P3.6���ó����뷽��  
   P3REN |= 0x70;  //������������

   P3OUT |= 0x70;
	 
}


/**********************************************************************************************************
* �������ƣ�KeyScan
* �������ܣ�����ɨ�裬����0��ʾ�޼����£�1-9����������
**********************************************************************************************************/
unsigned char KeyScan(void)
{
  unsigned long i;
  unsigned char P3 ;
  P3 = P3OUT;
  P3OUT = (P3 &0x80)|(P3 &0x08) | 0x00;  //�˶δ������12864����ԭ��ͼһ��ʳ��Ч������
  if(0x70 == (P3IN & 0x70)) // û�а���������0
  {
    return 0;
  }
 
  for(i = 0;i < 12000;i ++);  // �м����£���ʱ�� ���޸�
  
 // ɨ��KEY1 - KEY3
  P3 = P3OUT;
  P3OUT = (P3 & 0x80)|(P3 & 0x08) | 0x06;
  if(0x70 != (P3IN & 0x70)) 
  {
    switch((P3IN & 0x70))
    {
    case 0x60:
      return 1;
    case 0x50:
      return 2;
    case 0x30:
      return 3;      
  
    default:
      return 0; 
    }
  } 

  // ɨ��KEY4 - KEY6
  P3 = P3OUT;
  P3OUT = (P3&0x80)|(P3 &0x08) | 0x05;
  if(0x70 != (P3IN & 0x70))
  {
    switch((P3IN & 0x70))
    {
    case 0x60:
      return 4;
    case 0x50:
      return 5;
    case 0x30:
      return 6;     
    default:
      return 0; 
    }
  }    

  // ɨ��KEY7 - KEY9
  P3 = P3OUT;
  P3OUT = (P3&0x80)|(P3 &0x08) | 0x03;
  if(0x70 != (P3IN & 0x70)) 
  {
    switch((P3IN & 0x70))
    {
    case 0x60:
      return 7;
    case 0x50:
      return 8;
    case 0x30:
      return 9;      
    default:
      return 0; 
    }
  }  
  return 0;
}