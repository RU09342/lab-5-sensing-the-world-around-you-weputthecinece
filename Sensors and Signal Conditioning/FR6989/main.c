#include <msp430.h> 


/**
 * main.c
 */

unsigned int adcData;
char lsb;
char msb;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// sit boy
	
	while (1){                  // don't return 0

	    CSCTL0_H = CSKEY >> 8;
	    CSCTL1   = DCOFSEL_3 | DCORSEL;
	    CSCTL2   = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;
	    CSCTL3   = DIVA__1 | DIVS__1 | DIVM__1;
	    CSCTL0_H = 0;

	    P2SEL0 |= BIT0;                         // UART TX
	    UCA0CTLW0 |= UCSWRST;                   // State machine reset
	    UCA0CTLW0 |= UCSSEL1;                   // Uses SMCLK as source
	    UCA0BR0    = 52;                         // Modulation
	    UCA0MCTLW  = UCBRF_1 | UCOS16 | 0x4900;
	    UCA0BR1    = 0x00;                         // Modulation
	    UCA0CTLW0 &= ~UCSWRST;

	    P8SEL0    |= BIT7;                                  // ADC data comes in to 1.1
	    ADC12MCTL0  = ADC12INCH_4;
	    ADC12CTL0  = ADC12ON + ADC12SHT0_8 + ADC12MSC;      // turn on ADC and set sample time and set multi signal conversion
	    ADC12CTL1  = ADC12SHP + ADC12CONSEQ_2;              // sets signal based on timer
	    ADC12CTL0 |= ADC12ENC |  ADC12SC;                   // enable and start conversion

	    TA0CCTL0 = CCIE;                // enable interrupts
	    TA0CTL   = TASSEL_2 + MC_1;     // small clk, up mode
	    TA0CCR0  = 32767;               // sample rate 1 Hz

	    __bis_SR_register(LPM4_bits + GIE);     // enter low power mode 4, interrupts enabled
	}
	return 0;   // unreachable intentionally
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A (void) {

    adcData = ADC12MEM0;                // store ADC to memory
    msb = adcData >> 8;                 // shift 12 bit input so msb reads 0000 followed by four most sig bits of input
    lsb = adcData & 0xFF;               // lsb gets last eight bits of 12 bit input

    UCA0TXBUF = msb;                    // send msb

    if (UCA0IFG && UCTXIFG){            // wait for msb to go through
        UCA0TXBUF = lsb;                // then send lsb
    }
}
