#include <msp430g2553.h> 

void main (void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WatchDog Timer
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    BCSCTL1 &=~XTS;
    BCSCTL3 |= LFXT1S1;
	TA1CTL|=TASSEL_1+TACLR+MC_3+ID_0;//采取外部晶振32.768k，计数清零，增减计数模式，不分频，
        //#define TASSEL_1            (1*0x100u) /* Timer A clock source select: 1 - ACLK  */
        //#define TACLR               (0x0004u)  /* Timer A counter clear */
        //#define MC_3                (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
        //#define ID_0                (0*0x40u)  /* Timer A input divider: 0 - /1 */
        TA1CCTL0=CCIE;//启用定时器中断
	TA1CCR0=1684;//计数 1S
        // 32.768 kHz = 32768 Hz = 1/32768 s
        // countnum = 0.5s / (1/32768s) = 16384 
	P1DIR|=BIT0;
        P1OUT|=BIT0;
	_EINT();//LPM4;
	while(1);
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void ta10_isr(void) 
{
  P1OUT^=BIT0;
}
