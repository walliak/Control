#include <msp430g2553.h> 
void main (void)
{
    WDTCTL=WDTPW+WDTHOLD;
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
    BCSCTL1 &=~XTS;
    BCSCTL3 |= LFXT1S1;
    TA1CTL|=TASSEL_1+TACLR+MC_1+ID_0;//采取内部时钟源1.04M，计数清零，增减计数模式，八分频，
    //#define TASSEL_2            (2*0x100u) /* Timer A clock source select: 2 - SMCLK */
    //#define TACLR               (0x0004u)  /* Timer A counter clear */
    //#define MC_3                (3*0x10u)  /* Timer A mode control: 3 - Up/Down */
    //#define ID_3                (3*0x40u)  /* Timer A input divider: 3 - /8 */
    TA1CCTL0=CCIE;//启用定时器中断
    TA1CCR0=1000;//计数 1S
    // 1*(10^6) Hz ---- T = 0.000,001 s 
    // time = 0.000,001 * 8 * 62500 = 0.5 s
    P1DIR|=BIT0;
    _EINT();//LPM4;
    while(1);
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void ta10_isr(void) 
{
    P1OUT^=BIT0;
}
