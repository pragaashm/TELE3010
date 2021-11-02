/*
 * Lab_5_2.c
 *
 * Created: 12-Feb-20 1:38:23 PM
 * Author : praga
 */ 

#define F_CPU 16000000UL // System clock
#define USART_BAUDRATE 9600 // desired baud rate
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1) // UBRR value
#include <avr/io.h>	
#include "pinDefines.h"

/* Simple loopback UART program. */



int main(void)

{
	DDRD = 0xFC; //Setter de riktige LED-portene som output
	DDRB = 0x03;
	UBRR0 = BAUD_PRESCALE; // Set UBBR according to system clock and desired baud rate
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Turn on the transmission and reception circuitry
	while(1)
	{
		do {} while(!(UCSR0A & (1<<RXC0))); // Wait for incoming data
		/* Next line outputs received data. This is possible due to UDR being separate
		registers for transmission and reception */
		UDR0 = UDR0;
	}
}

