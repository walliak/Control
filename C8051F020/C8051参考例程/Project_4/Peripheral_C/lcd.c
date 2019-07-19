#include <c8051f020.h>
#include <math.h>
#include "lcd.h"
#include "character.h"
/******************************
12864LCD��
��*��=64*128�����ص�

********************************/
sbit  SCK=  P3^4;
sbit  SDA=  P3^5;
 
void Delayms(unsigned int time)
{
	int i;
	while(time--)
	for(i=0;i<=20;i++);
}

void WrateC(unsigned char com)				//��������	��LCDWrite�Ⱥ�������

{
    unsigned char data i,j,k;
	    ClrLCDRS;  
		for(i=0;i<8;i++)
	    { 
			 j=com;	 			 
			 SDA=com&0x80; 
			 SCK=0;
			 for(k = 0;k < 3;k ++);//��ʱ
	         SCK=1;	
			 for(k = 0;k < 3;k ++);//��ʱ     
			 com=j<<1;
		}
		SetLCDRS;
}

void WrateD(unsigned char dat)			  //��������	 ��LCDWrite�Ⱥ�������

{
    unsigned char data i,j,k;
	    SetLCDRS;  
		for(i=0;i<8;i++)
	    { 
			 j=dat;
			 
			 SDA=dat&0x80;
			 SCK=0;
			 for(k = 0;k < 3;k ++);//��ʱ
	         SCK=1;	  
			 for(k = 0;k < 3;k ++);//��ʱ   
			 dat=j<<1;
		}
		ClrLCDRS;
}

void LCDWrite(unsigned char type,unsigned char dat)		//	#define		W_CMD		1		#define		W_DAT		0		��LCD������Ϣ ����/����	

{ 

	if(type)
	{
		WrateC(dat);
	}
	else
	{
		WrateD(dat);
	}
}

void newLCDInit()						  //LCD��ʼ������,���Ų�������ϵͳ��ʼ�������ˣ�ע�⴮��ģʽ��LCD��ʱ�����������߶�Ҫ����ΪPģʽ������
{
// 	P3MDOUT |= BIT(4) + BIT(5); //P3.4 P3.5 LCD IO ������
 //   P74OUT |= BIT0;             //P4.0-P4.4����Ϊ�������
	SetLCDRST;
	Delayms(10);
	ClrLCDRST;
	Delayms(10);
	SetLCDRST;
	Delayms(10);
	LCDWrite(W_CMD,0xE2);	//�����λ
	LCDWrite(W_CMD,0xA3);//Bais set		��ʾƫѹ
	LCDWrite(W_CMD,0xA0);//ADC seg����ѡ�� 0xa0������0xA1���Ҿ���
	LCDWrite(W_CMD,0xC0);//com output scan direction��com����ѡ�� 0xc0������0xC8���¾���
	LCDWrite(W_CMD,0x26);
	Delayms(5);

	

	LCDWrite(W_CMD,0x2C);//�ڲ���Դ����
	Delayms(10);
	LCDWrite(W_CMD,0x2E);//����ָ����ʱ��2ms
	Delayms(10);
	LCDWrite(W_CMD,0x2F);
	Delayms(10);

//	LCDWrite(W_CMD,0x24);//��ѹ�����Ĵ�����λ ��Χ��0x21-0x27 
	LCDWrite(W_CMD,0x81);//��ѹģʽѡ��
	LCDWrite(W_CMD,0x20);//��ѹ�����Ĵ�����λ ��Χ��0x00-0x3f
	Delayms(10);
	LCDWrite(W_CMD,0xF8);
	LCDWrite(W_CMD,0x01);
    Delayms(5);
	LCDWrite(W_CMD,0xAF);//��ʾ��         
//	LCDWrite(W_CMD,0x40);//�����п�ʼ��ʾ
}
//
//---------------------------------------------
//LCD_set_XY: ����LCD���꺯��
//���������X��0��127  Y��0��7
//��д���ڣ�
//---------------------------------------------
void LCD_setXY(unsigned char X, unsigned char Y)	   //����LCD���꺯��X��0��127  Y��0��7 ,���÷�ʽ��LCD_setXY(0,0)   ���Ͻ�Ϊԭ��Ӵ��
{
	unsigned char gao,di;
	WrateC(0xB0 | Y); //ҳ
	gao = X & 0xf0;
	gao = gao >> 4;
	di = X & 0x0f;
	WrateC(0x10 | gao);  //set Column address MSB
    WrateC(0x00 | di);  //set column address LSB

}


void LCD_draw_point(unsigned char x,unsigned char y)    // ����Ϊԭ�㣡 X��0��127  Y��0��7 λ�û���  һ��һ�а˸���Ӵ�� 
{
	LCD_setXY(x,y);
	LCDWrite(W_DAT,0xff) ;
}

void Clear()								  //����
{
   unsigned char page,j;
	 for(page=0xB7;page>=0xB0;page--)  
    {  
	LCDWrite(W_CMD,page);
	LCDWrite(W_CMD,0x10);
	LCDWrite(W_CMD,0x00);  
     for(j=0;j<128;j++)  
        {  
         WrateD(0x00);  
        }  
    } 
}

/*
void set_page_add(unsigned char page) 		  //��ҳ
{  
	LCDWrite(W_CMD,0xB7-page);
}

void set_column_add(unsigned char column)
{
        unsigned char column_H,column_L;
          column_H=(column>>4)|0x10;      //�������ݸ�ʽ
          column_L=column&0x0f;           //�������ݸ�ʽ
		  LCDWrite(W_CMD,column_H);
		  LCDWrite(W_CMD,column_L);
}

void s_out_W(unsigned char j)
{  
  unsigned char u,k;  
  for(u=0;u<8;u++)
       { 
        SDA=j&0x01;
		SCK=0;
		for(k = 0;k < 5;k ++);//��ʱ
	    SCK=1;	  
		for(k = 0;k < 5;k ++);//��ʱ
        j>>=1;
       }   
}

void w_dat_W(unsigned char dat)  
{    
 	SetLCDRS;    
 	s_out_W(dat); 
} 
*/

void DrawPoint(unsigned char x,unsigned char y)		//��������ͬһ��ʾ�ֽ�ʱ,����ԭʼ���ݣ����㣡	   LCD���½�Ϊ����ԭ�� x:0~127 y :0~63
{
    unsigned char senddat,yy;
	static unsigned char DataOld=0,yOld=0,xOld=0;
	yy=(int)(y/8);
	if((yy==yOld)&&(x==xOld))
	   senddat = DataOld | (0x80>>(y%8));
	else
	   senddat = 0x80>>(y%8);
	LCD_setXY(x,abs(yy-7));
	LCDWrite(W_DAT,senddat);
	DataOld = senddat;
	yOld=yy;
	xOld=x;
}


/*********************************************************************
*����Ļ����ʾһ���ַ���16*8���㣬��16�ֽڣ�
*������C�ַ�  	row ��:0~3  col ��:0~15
*********************************************************************/
void Drawchar(unsigned char C,unsigned char row,unsigned char col)		  	 
{	
    unsigned char b,Row,Col;
    unsigned char k;
	k=C-0x20;
	Row=(63-(16*row));
	Col=8*col;

	for(b = 0;b<16;b++)
	{
	  unsigned char F;
	  F=2*b;
	 if(b<8)
	 {
	  if((AsciiFontData[k][b]&0x80)!=0)
	  DrawPoint(Col+b,Row);
	  	
	  
	  if((AsciiFontData[k][b]&0x40)!=0)
	  DrawPoint(Col+b,Row-1);
	   	
	  if((AsciiFontData[k][b]&0x20)!=0)
	  DrawPoint(Col+b,Row-2);
	   	
	  if((AsciiFontData[k][b]&0x10)!=0)
	  DrawPoint(Col+b,Row-3);

	  if((AsciiFontData[k][b]&0x08)!=0)
	  DrawPoint(Col+b,Row-4);
	  	
	  if((AsciiFontData[k][b]&0x04)!=0)
	  DrawPoint(Col+b,Row-5);
	   
	  if((AsciiFontData[k][b]&0x02)!=0)
      DrawPoint(Col+b,Row-6);
	  	
	  if((AsciiFontData[k][b]&0x01)!=0)
	  DrawPoint(Col+b,Row-7);
	  }
	  else
	  {
	   if((AsciiFontData[k][b]&0x80)!=0)
	  DrawPoint(Col+b-8,Row-8);
	  	
	  
	  if((AsciiFontData[k][b]&0x40)!=0)
	  DrawPoint(Col+b-8,Row-9);
	   	
	  if((AsciiFontData[k][b]&0x20)!=0)
	  DrawPoint(Col+b-8,Row-10);
	   	
	  if((AsciiFontData[k][b]&0x10)!=0)
	  DrawPoint(Col+b-8,Row-11);

	  if((AsciiFontData[k][b]&0x08)!=0)
	  DrawPoint(Col+b-8,Row-12);
	  	
	  if((AsciiFontData[k][b]&0x04)!=0)
	  DrawPoint(Col+b-8,Row-13);
	   
	  if((AsciiFontData[k][b]&0x02)!=0)
      DrawPoint(Col+b-8,Row-14);
	  	
	  if((AsciiFontData[k][b]&0x01)!=0)
	  DrawPoint(Col+b-8,Row-15);
	  }	  
	
	}

}

/*********************************************************************
*����Ļ����ʾһ���ַ�
*������C�����ַ���  	row ��ʼ��:0~3  low ��ʼ��:0~15
*********************************************************************/
void DrawcharS(unsigned char *C,unsigned char row,unsigned char col)		//ÿ�����16���ַ�������16�����У���4��		���Ͻ�ԭ��
{
  int flag=0,i=0;
  unsigned char R,L,TOTAL;
  TOTAL=(row*16)+col;
  if(TOTAL>63||row>3||col>15)
   {flag=1;}

  while(flag==0)
  {
   if(*C!='\0')
   {
     R=	(TOTAL+i)/16 ;
   	 L=	(TOTAL+i)%16;
	 Drawchar(*C,R,L);
	 C++;
	 i++;
	 if((TOTAL+i)>63)
	  {
	   	 flag=1;
	  }
   }
   else
   {
     flag=1;
   }
 }

}

/***********************************************
*���ִ�б��

*����Ļ����ʾһ�����֣�16*16���㣬��32���ֽڣ�
*������ CΪ������DzkCode�е��±�λ�ã�
		row ��LCD������ʾ���� 0-3��
		col ��LCD������ʾ���� 0-7��
*ɨ�跽ʽ������--�����Һ�����
		   ��λ��ǰ

**********************************************/
void Drawhanzi(unsigned char C,unsigned char row,unsigned char col)		  //row ��:0~3  col ��:0~7   ÿ������ռ16*16����	 ���Ͻ�ԭ��
{	
    unsigned char b,Row,Col;
    unsigned char k;
	k=C;
	Row=(63-(16*row));
	Col=16*col;

		for(b = 0;b<32;b++)
	{
	 if(b<16)
	 {
	  if((DzkCode[k][b]&0x80)!=0)
	  DrawPoint(Col+b,Row);
	  	
	  
	  if((DzkCode[k][b]&0x40)!=0)
	  DrawPoint(Col+b,Row-1);
	   	
	  if((DzkCode[k][b]&0x20)!=0)
	  DrawPoint(Col+b,Row-2);
	   	
	  if((DzkCode[k][b]&0x10)!=0)
	  DrawPoint(Col+b,Row-3);

	  if((DzkCode[k][b]&0x08)!=0)
	  DrawPoint(Col+b,Row-4);
	  	
	  if((DzkCode[k][b]&0x04)!=0)
	  DrawPoint(Col+b,Row-5);
	   
	  if((DzkCode[k][b]&0x02)!=0)
      DrawPoint(Col+b,Row-6);
	  	
	  if((DzkCode[k][b]&0x01)!=0)
	  DrawPoint(Col+b,Row-7);
	  }
	  else
	  {
	   if((DzkCode[k][b]&0x80)!=0)
	  DrawPoint(Col+b-16,Row-8);
	  	
	  
	  if((DzkCode[k][b]&0x40)!=0)
	  DrawPoint(Col+b-16,Row-9);
	   	
	  if((DzkCode[k][b]&0x20)!=0)
	  DrawPoint(Col+b-16,Row-10);
	   	
	  if((DzkCode[k][b]&0x10)!=0)
	  DrawPoint(Col+b-16,Row-11);

	  if((DzkCode[k][b]&0x08)!=0)
	  DrawPoint(Col+b-16,Row-12);
	  	
	  if((DzkCode[k][b]&0x04)!=0)
	  DrawPoint(Col+b-16,Row-13);
	   
	  if((DzkCode[k][b]&0x02)!=0)
      DrawPoint(Col+b-16,Row-14);
	  	
	  if((DzkCode[k][b]&0x01)!=0)
	  DrawPoint(Col+b-16,Row-15);
	  }	  
	
	}
}

/***********************************************
*������б��

*����Ļ����ʾһ�����֣�16*16���㣬��32���ֽڣ�
*������ CΪ������DzkCode�е��±�λ�ã�
		row ��LCD������ʾ���� 0-3��
		col ��LCD������ʾ���� 0-7��
*ɨ�跽ʽ������--�����Һ�����
		   ��λ��ǰ

**********************************************/
void Drawhanzifix(unsigned char C,unsigned char row,unsigned char col)		  //row ��:0~3  col ��:0~7   ÿ������ռ16*16����	 ���Ͻ�ԭ��
{	
    unsigned char b,Row,Col;
    unsigned char k;
	k=C;
	Row=(63-(16*row));
	Col=16*col;

		for(b = 0;b<32;b++)
	{
	 if(b<16)
	 {
	  if(((DzkCode[k][b]-Fix[b])&0x80)!=0)
	  DrawPoint(Col+b,Row);
	  	
	  
	  if(((DzkCode[k][b]-Fix[b])&0x40)!=0)
	  DrawPoint(Col+b,Row-1);
	   	
	  if(((DzkCode[k][b]-Fix[b])&0x20)!=0)
	  DrawPoint(Col+b,Row-2);
	   	
	  if(((DzkCode[k][b]-Fix[b])&0x10)!=0)
	  DrawPoint(Col+b,Row-3);

	  if(((DzkCode[k][b]-Fix[b])&0x08)!=0)
	  DrawPoint(Col+b,Row-4);
	  	
	  if(((DzkCode[k][b]-Fix[b])&0x04)!=0)
	  DrawPoint(Col+b,Row-5);
	   
	  if(((DzkCode[k][b]-Fix[b])&0x02)!=0)
      DrawPoint(Col+b,Row-6);
	  	
	  if(((DzkCode[k][b]-Fix[b])&0x01)!=0)
	  DrawPoint(Col+b,Row-7);
	  }
	  else
	  {
	   if(((DzkCode[k][b]-Fix[b])&0x80)!=0)
	  DrawPoint(Col+b-16,Row-8);
	  	
	  
	  if(((DzkCode[k][b]-Fix[b])&0x40)!=0)
	  DrawPoint(Col+b-16,Row-9);
	   	
	  if(((DzkCode[k][b]-Fix[b])&0x20)!=0)
	  DrawPoint(Col+b-16,Row-10);
	   	
	  if(((DzkCode[k][b]-Fix[b])&0x10)!=0)
	  DrawPoint(Col+b-16,Row-11);

	  if(((DzkCode[k][b]-Fix[b])&0x08)!=0)
	  DrawPoint(Col+b-16,Row-12);
	  	
	  if(((DzkCode[k][b]-Fix[b])&0x04)!=0)
	  DrawPoint(Col+b-16,Row-13);
	   
	  if(((DzkCode[k][b]-Fix[b])&0x02)!=0)
      DrawPoint(Col+b-16,Row-14);
	  	
	  if(((DzkCode[k][b]-Fix[b])&0x01)!=0)
	  DrawPoint(Col+b-16,Row-15);
	  }	  
	
	}
}

/***********************************************
*��ʾһ�к���

*������ CΪһ���±�λ�ã�
		row ��LCD������ʾ���� 0-3��
		col ��LCD������ʾ���� 0-7��

*ÿ�������ʾ8�����֣��Զ�����

**********************************************/
void DrawhanziS(unsigned char *C,unsigned char row,unsigned char col)	
{
  int flag=0,i=0;
  unsigned char R,L,TOTAL;
  TOTAL=(row*8)+col;
  if(TOTAL>63||row>3||col>15)
   {flag=1;}

  while(flag==0)
  {
   if(*C!='\0')
   {
     R=	(TOTAL+i)/8 ;
   	 L=	(TOTAL+i)%8;
	 Drawhanzifix(*C,R,L);
	 C++;
	 i++;
	 if((TOTAL+i)>63)
	  {
	   	 flag=1;
	  }
   }
   else
   {
     flag=1;
   }
 }

}


