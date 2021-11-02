/*
 * t_1.cpp
 *
 * Created: 04-Jun-20 3:12:06 PM
 * Author : praga
 */ 
#define F_CPU 160000000L
#include <avr/io.h>
#include <avr/delay.h>


int main(void)
{
DDRB = 1<<DDB5; // 0b00100000 - PB5 output - other PB pins inputs
PORTB = (1<<PORTB0); // Pullup om PB0
PORTB |= 1<<PORTB5; // PB5 high - turn on led
PORTB ^= 1<<PORTB5; // Toggle LED pin/bit 5 in PORTB register
PINB |= (1<<PINB5); // Toggle LED pin/bit 5 in PORTB register
// Main loop
do {
if(!(PINB & (1<<PINB0)) ){
PINB |= (1<<PINB4); // Toggle bit 4 in PORTB register
}
} while (1); // End main loop
}