/*
 * led.c
 *
 *  Created on: 2019��7��13��
 *      Author: Think
 */
#include "MSP430F5529.h"

void LedInit(void)
{
	P1DIR |= BIT0;
	P4DIR |= BIT7;
}



