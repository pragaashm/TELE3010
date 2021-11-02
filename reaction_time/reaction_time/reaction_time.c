/*!***************************************************************************
 *  Mikroprosessorsystemer                                                   *
 *  Labøving reaksjonstidsmåler                                              *
 *  NTNU Insitutt for elektrofag og fornybar energi                          *
 *  Rolf Kristian Snilsberg                                                  *
 *  Device: ATmega328P in Xplained mini                                      *
 *****************************************************************************
 */

/*!
The application is meant to be run on ATmega328P in Xplained mini or Arduino 
UNOwith 16MHz system clock. It assumes a button is connected to input capture 1
i.e. PB0, one led to PB5 (or more of port B) and usart0 to a terminal.

The application waits for a low level on PINB0 (button pressed to start). 
It will then wait a pseudo random time before outputting high on PORTB5 and 
(thus turning on or all leds) and starting time measurement. The button 
shall then be pressed again as soon as possible. The reaction time (in ms) from
the leds turn on until the button is pressed is measured and output on USART in 
ASCII format. The communication format is 9600 baud, 8 data bits, 1 stop bit 
and no parity (8N1).
***/


// Includes
#include "reaction_time.h"
#include "timer_routines.h" 
#include "usart_routines.h"


// Main.
int main (void)
{
	uint16_t reaction_time_ms;
	char init_string[] = "\r\nPress button to start...";
	char started_string[] = {"Started!\r\n"};
	char reaction_time_string[] = {"1234ms \r\n"};  // initialized to 4 digit value
	char too_slow_string[] = {"Too slow!\r\n"};
	char cheater_string[] = {"Cheater!\r\n"};

	USART_TX_Init(BAUD_VALUE);

	DDRB = (1<<DDB5);  // PB5 output.
	PORTB = (0<<PORTB5) | (1<<PORTB0);  // PB5 high, i.e. led off, pull-up on PB0 enabled
	
	Timer1_Init_Capture();

	do {
		USART_Transmit_String(init_string);

		// Wait for key press and use debouncing.
		do {} while ( PINB & (1 << PINB0) );  // Wait for PINB0 to be pushed.
		_delay_ms(10);
		do {} while ( !(PINB & (1 << PINB0)) );  // Wait for PINB0 to be released.

		USART_Transmit_String(started_string);

		if(wait_random_time()) {

			reaction_time_ms = measure_reaction_time();

	/* 		Convert reaction time to ascii value and insert it into string. It 
			divides modulo 10 thus giving the remainder */
			if (reaction_time_ms != 0 ) {
				int8_t count;
				for (count = 3 ; count >= 0 ; count--) {
					reaction_time_string[count] = reaction_time_ms%10 + '0';
					reaction_time_ms /= 10;
				}
				USART_Transmit_String(reaction_time_string);
			} else {
				USART_Transmit_String(too_slow_string);
			}
		} else { 
			USART_Transmit_String(cheater_string);
		}
		_delay_ms(1000);  // Delay to avoid starting new measurement prematurely

	} while (1);
}

