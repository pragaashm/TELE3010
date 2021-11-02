/*
 * make_avr_ex_6_1.c
 *
 * Created: 28.01.2019 23:04:31
 * Author : rksni
 */ 

#define F_CPU 16e6

#include <avr/io.h>
// #include <util/delay.h>  // not needed in this code


int main(void) {
	// -------- Inits --------- //
	PORTD |= (1 << PORTD2);  /* initialize pullup resistor on our input pin */
	DDRB = 0xff;          /* set up all LEDs for output */

	// ------ Event loop ------ //
	while (1) {
// 		if (PIND & (1<<PIND2) == 0) {  // equivalent function to code below
// 		if (!(PIND & (1<<PIND2))) {  // equivalent to code below
		if (bit_is_clear(PIND, PIND2)) { // look for button press
				PORTB = 0b00111000; // button pressed
		} else {
			PORTB = 0b00000111;     // button not pressed
		}
	} /* End event loop */
//	return (0);
}

