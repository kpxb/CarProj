#include <msp430.h> 

void Timer_A0_Config(void);
void Car_Run(void);

int flag;

int main(void)
{
    flag = 0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Timer_A0_Config();
	 __bis_SR_register(LPM0_bits | GIE);

	 while(1)
	 {
	     while(flag)
	     {
	         Car_Run();
	     }

	 }
}

void Timer_A0_Config(void)
{
    TA0CCTL0|= CCIE;
    TA0CCR0 = 10000;
    TA0CTL|= TASSEL__SMCLK | MC__CONTINUOUS;
}

void Car_Run(void)
{
    //Unfinished
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    static int i = 0;
    i += 1;
    if(i == 6000)
    {
        flag = 1;
        TA0CTL|= MC_0;
    }
    TA0CCR0 += 10000;                             // Add Offset to TACCR0
}
