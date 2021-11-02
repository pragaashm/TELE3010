/*
 * Lab_1.c
 *
 * Created: 15-Jan-20 1:44:06 PM
 * Author : praga
 */ 

/* Defines */
#define F_CPU 16000000UL // Tell delay.h clock frequency
/* Includes */
#include <avr/io.h> /* Defines pins, ports, etc */
#include <util/delay.h> /* Functions to waste time */

int main(void)
{
	// Inititalization
	DDRB = (1<<DDB5);// 0b00100000 - PB5 output - other PB pins inputs
	PORTB = 1<<PORTB5; // PB5 high - turn on led
	// Main loop
	while (1)
	{ // End main loop
		PORTB = 1<<PB5;
		_delay_ms(400);
		PORTB = 0<<PB5;
		_delay_ms(600);
	}
	
	// return (0); // Never reached/not needed
}