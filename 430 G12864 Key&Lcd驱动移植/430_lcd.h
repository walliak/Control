#ifndef __LCD_H__
#define __LCD_H__

	#define		W_CMD		1			//指令
	#define		W_DAT		0			//数据
	#define SetLCDRS  P3OUT |= 0x08 		 //宏定义，对LCD_RS进行位操作,移植修改部分*****,
	#define ClrLCDRS  P3OUT &= ~0x08
	#define SetLCDRST P3OUT |= 0x80 		 //宏定义，对LCD_RST进行位操作
	#define ClrLCDRST P3OUT &= ~0x80

	void Delayms(unsigned int ms);
	//unsigned char RightShiftOperation(unsigned char dat,unsigned char shiftcount);
        //unsigned char LeftShiftOperation(unsigned char dat,unsigned char shiftcount);
	void WrateC(unsigned char com);
	void WrateD(unsigned char dat);
	void LCDWrite(unsigned char type,unsigned char dat);
	void newLCDInit();
	void LCD_setXY(unsigned char X, unsigned char Y);
	void LCD_draw_point(unsigned char x,unsigned char y);
	void DrawPoint(unsigned char x,unsigned char y);
	void Clear();
	void Drawchar(unsigned char a,unsigned char row,unsigned char col);
	void Drawchinese(unsigned char a,unsigned char row,unsigned char col);
	void DrawcharS(unsigned char* a,unsigned char row,unsigned char col);



#endif