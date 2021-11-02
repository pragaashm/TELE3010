/*****************************************************************************
 *  Mikroprosessorsystemer                                                   *
 *  Labøving 8                                                               *
 *  Høgskolen i Sør-Trøndelag - Rolf Kristian Snilsberg                      *
 *                                                                           *
 *  Device: ATmega2560 in STK600                                             *
 *****************************************************************************
 */

/*** Timer routines. ***/

//	Defines
/*	1024x prescaler, i.e. 10 bit. This will give a 16-timer a a resolution of 
	1024/16MHz = 64us and range of 2^16*64us = 4.096 seconds. More than 
	sufficient for the task. */
#define T1_PRESCALE_BITS 10  


//	Includes
#include "timer_routines.h"


//	Functions.

/*	Configre Timer1 with 1024x prescaling and input capture noise supression 
	enabled.
 */
void Timer1_Init_Capture(void)
{
	TCCR1B = (1<<ICNC1)|(1<<CS12)|(1<<CS10);   // Input capture noise suppression. 1024x prescaler.
	PCMSK0 = (1<<PCINT0);  // enable pin change interrupt tracking on PPB0 = CINT0
}


/*!	Waits a pseudo random time from aproximately 1 to 5 seconds. Blocking 
	It uses the last 6 bits of counter1 when the it's called, multiplies this 
	with 16*4=64ms delay thus giving possible delays of x*64 mseconds + 0,64,128,..4096 ms. 
 */
uint8_t wait_random_time(void)
{
	uint8_t no_cheat = 1;
	PCIFR = (1<<PCINT0);
	uint16_t delay = (TCNT1L & 0x3F) + 16; // 0x3F = 0b 0011 1111 =63, 64x64=4096
	while (delay > 0) {
		_delay_ms(64);
		delay--;
	}
	if (PCIFR & (1<<PCINT0)) {
		no_cheat = 0;
	}
// 	uint16_t delay = ((TCNT1L & 0x3F) + 16)<<4; 
// 	while ((delay > 0) && (PINB & (1 << PINB0))) {
// 		_delay_ms(4);
// 		delay--;	
// 	}
// 	if (!(PINB & (1 << PINB0))) {
// 		no_cheat = 0;
// 	}
	return(no_cheat);	
}


/*	Measures reaction time from a led is lit until key is pressed in ms by
	using input capture. Blocking. It uses overflow in timer for timeout and 
	returns 0 if so, assuming 0 is never reachable. 
	Clock frequency is defined with F_CPU.
 */
uint16_t measure_reaction_time(void)
{
	uint16_t start_time, stop_time;
	uint32_t reaction_time = 0;

	TIFR1 |= (1<<ICF1) | (1<<TOV1);  // Clear flags.
	TCNT1 = 0;
	PORTB |= (1<<PORTB5);
	start_time = 0;
	do {} while ( !(TIFR1 & ((1<<ICF1)|(1<<TOV1)) )  );  // Wait for a input capture event to happen.
	PORTB &= ~(1<<PORTB5);
	if ( !(TIFR1 & (1<<TOV1)) ) {
		stop_time = ICR1;
		// Calcualtion of reaction time in milliseconds
		reaction_time = ((uint32_t)(stop_time-start_time) << T1_PRESCALE_BITS)/(F_CPU/1000);
	} else {
		reaction_time = 0;
	}

	return (uint16_t)reaction_time;		
}
