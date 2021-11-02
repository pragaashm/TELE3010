//Main purpose of this assignment is to study the generated assembly code. This code is automatically
//generated after a debugging session. Can be found in the project folder (project_name.iss)

#include <avr/io.h>
int main(void)
{
	PORTB = (1<<PORTB0);
	DDRB = 1<<DDB5; // 0b00100000 - PB5 output - other PB pins inputs
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