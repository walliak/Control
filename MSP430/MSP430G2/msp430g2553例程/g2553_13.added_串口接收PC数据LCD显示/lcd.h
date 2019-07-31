#ifndef __LCD_H__
#define __LCD_H__

typedef struct LCDControl
{
	unsigned char row;
	unsigned char col;
}LCDControl;
void LCD_init();
void LCD_delayms(unsigned int ms);
void LCD_writeCmd(unsigned char com);
void LCD_writeData(unsigned char dat);
char LCD_setXY(unsigned char X, unsigned char Y);
void LCD_clear();
char LCD_drawPoint(unsigned char x , unsigned char y);
char LCD_drawCharAt( char ch , unsigned char col ,
					 unsigned char row);
char LCD_drawChar(char ch);
char LCD_drawStrAt( char * str , unsigned char len , unsigned char col ,
					unsigned char row);
char LCD_drawStr( char * str , unsigned char len );
char LCD_clearLine(unsigned char row);
#endif