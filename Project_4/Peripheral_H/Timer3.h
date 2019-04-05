#ifndef _TIMER3_H_
#define	_TIMER3_H_		
		extern unsigned int timeUnit;
		extern unsigned long timeTotal;
		extern unsigned char timeFlag;
						
		void Timer_Init();
		void OpenTimer3();
		void CloseTimer3();
#endif