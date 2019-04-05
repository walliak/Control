#ifndef _INIT_H_
#define _INIT_H_
	
	#define SetBit(x,y) x|=(1<<y)
	#define ClrBit(x,y)	x&=~(1<<y)
	#define ReverseBit(x,y) x^=(1<<y)
	#define GetBit(x,y)	 ((x)>>(y)&1)
	#define uchar unsigned char
	void Init_Device(void);
	void DelayMSec(int time);
	void DelayPart(int time); 		
#endif