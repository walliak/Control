#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#include "delay.h" 



#define KEY0 PGin(2) //PG2
#define KEY1 PGin(3) //PG3
#define KEY2 PGin(4) //PG4
#define	KEY3 PGin(5) //PG5
#define KEY0_PRES 1 //KEY0 按下
#define KEY1_PRES 2 //KEY1 按下
#define KEY2_PRES 3 //KEY2 按下
#define KEY3_PRES 4 //KEY3 按下


void KEY_Init(void); //IO 初始化
void Button_Init(void);

uint8_t read_button0_GPIO(void);
uint8_t read_button1_GPIO(void);
uint8_t read_button2_GPIO(void);
uint8_t read_button3_GPIO(void);

void BTN1_PRESS_DOWN_Handler(void* btn);
void BTN2_PRESS_DOWN_Handler(void* btn);
void BTN3_PRESS_DOWN_Handler(void* btn);
void BTN4_PRESS_DOWN_Handler(void* btn);



#endif
