#include <c8051f020.h>
#include <math.h>
#include "lcd.h"
#include "character.h"
/******************************
12864LCD屏
宽*高=64*128个像素点

********************************/
sbit  SCK=  P3^4;
sbit  SDA=  P3^5;
 
void Delayms(unsigned int time)
{
	int i;
	while(time--)
	for(i=0;i<=20;i++);
}

void WrateC(unsigned char com)				//发送命令	由LCDWrite等函数调用

{
    unsigned char data i,j,k;
	    ClrLCDRS;  
		for(i=0;i<8;i++)
	    { 
			 j=com;	 			 
			 SDA=com&0x80; 
			 SCK=0;
			 for(k = 0;k < 3;k ++);//延时
	         SCK=1;	
			 for(k = 0;k < 3;k ++);//延时     
			 com=j<<1;
		}
		SetLCDRS;
}

void WrateD(unsigned char dat)			  //发送数据	 由LCDWrite等函数调用

{
    unsigned char data i,j,k;
	    SetLCDRS;  
		for(i=0;i<8;i++)
	    { 
			 j=dat;
			 
			 SDA=dat&0x80;
			 SCK=0;
			 for(k = 0;k < 3;k ++);//延时
	         SCK=1;	  
			 for(k = 0;k < 3;k ++);//延时   
			 dat=j<<1;
		}
		ClrLCDRS;
}

void LCDWrite(unsigned char type,unsigned char dat)		//	#define		W_CMD		1		#define		W_DAT		0		向LCD传送信息 命令/数据	

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

void newLCDInit()						  //LCD初始化函数,引脚部份置于系统初始化部份了，注意串行模式下LCD的时钟数和数据线都要设置为P模式（？）
{
// 	P3MDOUT |= BIT(4) + BIT(5); //P3.4 P3.5 LCD IO 口设置
 //   P74OUT |= BIT0;             //P4.0-P4.4设置为推挽输出
	SetLCDRST;
	Delayms(10);
	ClrLCDRST;
	Delayms(10);
	SetLCDRST;
	Delayms(10);
	LCDWrite(W_CMD,0xE2);	//软件复位
	LCDWrite(W_CMD,0xA3);//Bais set		显示偏压
	LCDWrite(W_CMD,0xA0);//ADC seg镜像选择 0xa0正常，0xA1左右镜像
	LCDWrite(W_CMD,0xC0);//com output scan direction，com镜像选择 0xc0正常，0xC8上下镜像
	LCDWrite(W_CMD,0x26);
	Delayms(5);

	

	LCDWrite(W_CMD,0x2C);//内部电源管理，
	Delayms(10);
	LCDWrite(W_CMD,0x2E);//三条指令间隔时间2ms
	Delayms(10);
	LCDWrite(W_CMD,0x2F);
	Delayms(10);

//	LCDWrite(W_CMD,0x24);//电压调整寄存器高位 范围：0x21-0x27 
	LCDWrite(W_CMD,0x81);//电压模式选择
	LCDWrite(W_CMD,0x20);//电压调整寄存器低位 范围：0x00-0x3f
	Delayms(10);
	LCDWrite(W_CMD,0xF8);
	LCDWrite(W_CMD,0x01);
    Delayms(5);
	LCDWrite(W_CMD,0xAF);//显示开         
//	LCDWrite(W_CMD,0x40);//从首行开始显示
}
//
//---------------------------------------------
//LCD_set_XY: 设置LCD坐标函数
//输入参数：X：0－127  Y：0－7
//编写日期：
//---------------------------------------------
void LCD_setXY(unsigned char X, unsigned char Y)	   //设置LCD坐标函数X：0－127  Y：0－7 ,调用方式：LCD_setXY(0,0)   左上角为原点哟！
{
	unsigned char gao,di;
	WrateC(0xB0 | Y); //页
	gao = X & 0xf0;
	gao = gao >> 4;
	di = X & 0x0f;
	WrateC(0x10 | gao);  //set Column address MSB
    WrateC(0x00 | di);  //set column address LSB

}


void LCD_draw_point(unsigned char x,unsigned char y)    // 左下为原点！ X：0－127  Y：0－7 位置画点  一次一列八个点哟！ 
{
	LCD_setXY(x,y);
	LCDWrite(W_DAT,0xff) ;
}

void Clear()								  //清屏
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
void set_page_add(unsigned char page) 		  //换页
{  
	LCDWrite(W_CMD,0xB7-page);
}

void set_column_add(unsigned char column)
{
        unsigned char column_H,column_L;
          column_H=(column>>4)|0x10;      //调整数据格式
          column_L=column&0x0f;           //调整数据格式
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
		for(k = 0;k < 5;k ++);//延时
	    SCK=1;	  
		for(k = 0;k < 5;k ++);//延时
        j>>=1;
       }   
}

void w_dat_W(unsigned char dat)  
{    
 	SetLCDRS;    
 	s_out_W(dat); 
} 
*/

void DrawPoint(unsigned char x,unsigned char y)		//连续操作同一显示字节时,保留原始数据，画点！	   LCD左下角为坐标原点 x:0~127 y :0~63
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
*在屏幕上显示一个字符（16*8个点，共16字节）
*参数：C字符  	row 行:0~3  col 列:0~15
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
*在屏幕上显示一串字符
*参数：C【】字符串  	row 起始行:0~3  low 起始列:0~15
*********************************************************************/
void DrawcharS(unsigned char *C,unsigned char row,unsigned char col)		//每行最多16个字符，多于16个换行！共4行		左上角原点
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
*汉字带斜线

*在屏幕上显示一个汉字（16*16个点，共32个字节）
*参数： C为汉字在DzkCode中的下标位置，
		row 在LCD屏上显示的行 0-3；
		col 在LCD屏上显示的列 0-7；
*扫描方式：纵向--先左右后上下
		   高位在前

**********************************************/
void Drawhanzi(unsigned char C,unsigned char row,unsigned char col)		  //row 行:0~3  col 列:0~7   每个汉字占16*16个点	 左上角原点
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
*汉字无斜线

*在屏幕上显示一个汉字（16*16个点，共32个字节）
*参数： C为汉字在DzkCode中的下标位置，
		row 在LCD屏上显示的行 0-3；
		col 在LCD屏上显示的列 0-7；
*扫描方式：纵向--先左右后上下
		   高位在前

**********************************************/
void Drawhanzifix(unsigned char C,unsigned char row,unsigned char col)		  //row 行:0~3  col 列:0~7   每个汉字占16*16个点	 左上角原点
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
*显示一行汉字

*参数： C为一串下标位置，
		row 在LCD屏上显示的行 0-3；
		col 在LCD屏上显示的列 0-7；

*每行最多显示8个汉字，自动换行

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


