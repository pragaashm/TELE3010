/*
 * make_avr_ex_6_2.c
 *
 * Created: 28.01.2019 23:17:23
 * Author : rksni
 */ 

/*
	Demonstrates using state to detect button presses
*/

#include <avr/io.h>

// Defines from pinDefines.h moved to main.
#define BUTTON_PORT   PORTB
#define BUTTON_PIN    PINB
#define BUTTON        PORTB4  //PB4
#define LED_DDR       DDRB
#define LED_PORT      PORTB
#define LED0          PORTB5  // PB5




int main(void) 
{
	LED_PORT &= ~(0b00001111);  // or 0x0F
	// -------- Inits --------- //
	uint8_t buttonWasPressed; /* state */
	BUTTON_PORT |= (1 << BUTTON); /* enable the pullup on the button */
	LED_DDR = (1 << LED0); /* set up LED for output */
	// ------ Event loop ------ //
	while (1) {
		if (bit_is_clear(BUTTON_PIN, BUTTON)) { /* button is pressed now */
			if (buttonWasPressed == 0) { /* but wasn't last time through */
				LED_PORT ^= (1 << LED0); /* do whatever */
				buttonWasPressed = 1; /* update the state */
			} 
		} else { /* button is not pressed now */
			buttonWasPressed = 0; /* update the state */
		}
	} /* End event loop */
//	return (0); /* This line is never reached */
}

