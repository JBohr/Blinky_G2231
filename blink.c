//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  J. Stevenson
//  Texas Instruments, Inc
//  July 2011
//  Built with Code Composer Studio v5
//***************************************************************************************

#include <msp430.h>

#define LEDR BIT0
#define LEDG BIT6
#define BUTTONL BIT3



int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

	P1DIR |= LEDR + LEDG;			// Set P1.0, P1.6 to output direction, Keep P1.3 input

	P1OUT = ~(LEDR+LEDG);

	P1IE |= BUTTON; // P1.3 interrupt enabled

	P1IFG &= ~BUTTON; //P1.3 IFG Cleared

	//volatile unsigned int state = 1;

	__enable_interrupt(); // enable all interrupts

	for(;;) {
		volatile unsigned int i;	// volatile to prevent optimization

		P1OUT ^= 0x41;				// Toggle P1.0 using exclusive-OR

		i = 10000;					// SW Delay
		do i--;
		while(i != 0);
	}
	
	return 0;
}



// Port 1 interrupt service routine

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void)
{
	//Interrupt action
	P1OUT ^= LEDG;

	//Clear Interrupt
	P1IFG &= ~BUTTON;

}











