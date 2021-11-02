/*
   Press the button as quickly as you can after the LEDs light up.
   Your time is printed out over the serial port.
*/

// ------- Preamble -------- //
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "pinDefines.h"
#include "USART.h"
#include "support.h"


static inline void initTimer1(void) {

  TCCR1B |= (1 << CS12) | (1 << CS10) |(1<<ICNC1)
  
  /* Clock speed: 1 MHz / 1024*/

  TIFR1 |= (1<<ICF1); /*Time interrupt flag register / Time input capture flag*/
  TIMSK1 |= (1<<ICIE1); /*Timer/counter interrupt mask register / Timer1, ICI enabled */
  

}

int main(void) {
  uint16_t timerValue;

  // -------- Inits --------- //

  initUSART();
  initTimer1();
  LED_DDR = 0xff;                               /* all LEDs for output */
  BUTTON_PORT |= (1 << BUTTON);             /* enable internal pull-up */
  
  printString(ICIE1); 
  printString("\r\nReaction Timer:\r\n");
  printString("---------------\r\n");
  printString("Press any key to start.\r\n");
  printString(ICR1);

  // ------ Event loop ------ //
  while (1) {

    receiveByte();                                    /* press any key */
    printString("\r\nGet ready...");
    randomDelay();

    printString("\r\nGo!\r\n");
	
    LED_PORT = 0xff;                                     /* light LEDs */
    TCNT1 = 0;                                        /* reset counter */

    if (bit_is_clear(BUTTON_PIN, BUTTON)) {
            /* Button pressed _exactly_ as LEDs light up.  Suspicious. */
      printString("You're only cheating yourself.\r\n");
	  printString(ICR1);
    }
    else {
      // Wait until button pressed, save timer value.
      loop_until_bit_is_clear(BUTTON_PIN, BUTTON);
      timerValue = TCNT1 >> 4;
      /* each tick is approx 1/16 milliseconds, so we bit-shift divide */

      printMilliseconds(timerValue);
      printComments(timerValue);
    }

    // Clear LEDs and start again.
    LED_PORT = 0x00;
    printString("Press any key to try again.\r\n");

  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}