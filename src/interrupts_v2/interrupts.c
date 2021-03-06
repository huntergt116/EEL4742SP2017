#include <msp430.h>

#include <interrupt.h>

/* Instead of having preprocessor directives here to select which interrupt
 * vector declaration we need to use, we use the ISR() macro that was declared
 * in the interrupt.h header. This makes our code easier to read at the expense
 * of having an extra header file floating around.
 */
ISR(TIMER0_A0_VECTOR) {
	P1OUT	^=	0xff;		/* toggle the logic state of the pin */
}

int main(void) {
	/* WDT+ Module Setup */
	WDTCTL 	=	WDTPW | 	/* writing to the WDT+ registers
							 * requires the proper password */
				WDTHOLD;	/* stop the WDT+ module from counting */

	/* GPIO setup */
	P1DIR	=	0xff;		/* All pins as output on P1 */
	P1OUT	=	0x01;		/* Initialize all pins as low except for
							 * the lowest one */
	
	/* Timer_A Setup -- details on Chapter 12 of slau144j */
	/* capture/compare control register */
	TACCTL0	=	CCIE;		/* enable capture/compare interrupt */
	/* capture/compare value register */
	TACCR0	=	62499;		/* set count top */
	/* timer control */
	TACTL	=	TASSEL1 |	/* clock source selection - use ACLK */
				MC0 |		/* up mode - count to TACCR0, then reset */
				ID_3;		/* clock divider - divide ACLK by 8 */
	
	/* shut off CPU and enable interrupts */
	__bis_SR_register(CPUOFF | GIE);
}

/* vim:set ts=4 tw=79 syntax=c et: */
