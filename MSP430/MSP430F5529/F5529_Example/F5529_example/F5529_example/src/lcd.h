#ifndef _LCD_H__
#define  __LCD_H__
	#define		W_CMD	1			//ָ��
	#define		W_DAT	0			//����
	#define SetLCDRS 	 P3OUT |= BIT2 		 //�궨�壬��LCD_RS����λ����
	#define ClrLCDRS 	 P3OUT &= ~BIT2
	#define SetLCDRST	 P6OUT |= BIT4 		 //�궨�壬��LCD_RST����λ����
	#define ClrLCDRST 	 P6OUT &= ~BIT4
	void Delayms(unsigned int ms);
	void WrateC(unsigned char com);
	void WrateD(unsigned char dat);
	void LCDWrite(unsigned char type,unsigned char dat);
	void newLCDInit();
	void LCD_setXY(unsigned char X, unsigned char Y);
	void LCD_draw_point(unsigned char x,unsigned char y);
	void DrawPoint(unsigned char x,unsigned char y);
	void Clear();
	void clear_half();
	void Drawchar(unsigned char c,unsigned char row,unsigned char col);
	void DrawcharS(unsigned char *c,unsigned char row,unsigned char col);
	void drawint(unsigned int num,unsigned char row,unsigned char col);
	void drawfloat2_2(float num,unsigned char row,unsigned char col);


#endif
