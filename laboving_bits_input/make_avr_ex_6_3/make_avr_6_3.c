/*
 * make_avr_ex_6_3.c
 *
 * Created: 28.01.2019 23:59:51
 * Author : rksni
 */ 

#define F_CPU 16e6

// Pin defines instead of separate file.
#define BUTTON_PORT PORTB
#define BUTTON_PIN PINB
#define BUTTON PB0
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED0 PB5

#define DEBOUNCE_TIME  1000                            /* microseconds */


#include <avr/io.h>
#include <util/delay.h>


/* Function not documented in book. Rewritten to avoid multiple return-points.  */
uint8_t debounce(void) {
	uint8_t returnvalue = 0;
	if (bit_is_clear(BUTTON_PIN, BUTTON)) {      /* button is pressed now */
		_delay_us(DEBOUNCE_TIME);
		if (bit_is_clear(BUTTON_PIN, BUTTON)) {            /* still pressed */
			returnvalue = 1;
		} 
	}
	return returnvalue;
}


/*	Deboincing example. */
int main(void) {
	// -------- Inits --------- //
	uint8_t buttonWasPressed=0;                                 /* state */
	BUTTON_PORT |= (1 << BUTTON);     /* enable the pullup on the button */
	LED_DDR = (1 << LED0);                      /* set up LED for output */

	// ------ Event loop ------ //
	while (1) {
		if (debounce()) {                    /* debounced button press */
			if (buttonWasPressed == 0) {     /* but wasn't last time through */
				LED_PORT ^= (1 << LED0);     /* do whatever */
				PINB |= (1<<LED0);
				buttonWasPressed = 1;                      /* update the state */
			}
		} else {                                /* button is not pressed now */
			buttonWasPressed = 0;                        /* update the state */
		}
	}                                                  /* End event loop */
//	return 0;                            /* This line is never reached */
}

