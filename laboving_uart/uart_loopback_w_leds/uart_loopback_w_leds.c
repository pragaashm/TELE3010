/*
 * lab4_loopback.c
 *
 * Created: 10.02.2016 09:53:39
 *  Author: rolfkrs
 */ 

#define F_CPU 16000000UL  // System clock
#define USART_BAUDRATE 9600  // desired baud rate
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)  // UBRR value

#include <avr/io.h>

/*	UART program that receive UART data and output ASCII value on 8 LEDs 
	connected PB1,PB0,PD7-PD2. Sends received data back on UART. */
int main(void)
{
	uint8_t input;
	
	DDRD = 0xFC; // Output on PD2-PD7
	DDRB = (1<<DDB1)|(1<<DDB0); // Output on PB0-1
// 	DDRB = 0x3F; // Output on PB0-PB5
// 	DDRB = (1<<DDD6)|(1<<DDD7); // Output on PD6-7
	
	
	UBRR0 = BAUD_PRESCALE;         // Set UBBR according to system clock and desired baud rate
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Turn on the transmission and reception circuitry
	
    while(1)
    {
		do {} while(!(UCSR0A & (1<<RXC0)));	// Wait for incoming data
		// Read received data.
		input = UDR0;
		// Loopback received data to UART.
		UDR0 = input;
		input = ~input; // Invert as LED are active low. Remove/comment out is active high.
		// Output received data to PB1-0,PD7-2
		PORTB = input >> 6;	     // 0b10101110 >> 6 = 0b00000010 
		PORTD = input << 2;      // 0b10101110 << 2 = 0b10111000

//		Alternative using PB5-PB0 and PD7-PD6. Output pins need to be modified if used.
// 		PORTB = input >> 2;	     // 0b10101110 >> 2 = 0b00101011
// 		PORTD = input << 6;      // 0b10101110 << 6 = 0b10000000
    }
}
