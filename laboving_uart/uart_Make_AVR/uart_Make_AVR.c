/*
 * lab4_usart.c
 *
 * Created: 01.02.2016 12:08:46
 *  Author: rolfkrs
 */ 

/*
A simple test of serial-port functionality.
Takes in a character at a time and sends it right back out,
 displaying the ASCII value on the LEDs.
*/


// ------- Preamble -------- //
#include <avr/io.h>
//#include <util/delay.h>
//#include "pinDefines.h"
#include "USART.h"

int main(void) {
	char serialCharacter;
	// -------- Inits --------- //
	/* set up LEDs for output */  
	DDRD = 0xfC;
	DDRB = (1<<DDB1)|(1<<DDB0);

	initUSART();
	printString("Hello World!\r\n");                          /* to test */

	// ------ Event loop ------ //
	while (1) {
		serialCharacter = receiveByte();
		transmitByte(serialCharacter);
		PORTB = serialCharacter >> 6;	   // 0bABCDEFGH >> 6 = 0b000000AB
		PORTD = serialCharacter << 2;      // 0bABCDEFGH << 2 = 0bCDEFGH00

	/*	Alternative using PB5-PB0 and PD7-PD6.
		Output pins need to be modified if it is used.*/
// 		PORTB = serialCharacter >> 2;	   // 0bABCDEFGH >> 2 = 0b00ABCDEF
// 		PORTD = serialCharacter << 6;      // 0bABCDEFGH << 6 = 0bGH000000

//		PORTD = serialCharacter;     // display ascii/numeric value of character
	}	/* End event loop */
}
