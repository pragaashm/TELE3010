/*****************************************************************************
 *  Mikroprosessorsystemer                                                   *
 *  Labøving - timere blinking and PWM                                       *
 *  NTNU IES - Rolf Kristian Snilsberg				                         *
 *                                                                           *
 *  Device: ATmega328                                                        *
 *****************************************************************************
 */

/*	The application will first setup the 16-bit TCNT1 to give out a 1 HZ 
	heartbeat on the OC1A pin, i.e. PB1. It will then wait for a low input 
	on PB0/PB7 to change mode. The second mode is to give out a varying PWM duty 
	cycle on OC1A. Applying the signal to a LED will vary its light intensity.
	Code is generic for many AVRs but is run on a ATmega328P.
*/


//	Defines 
#define F_CPU 16000000UL     // 1MHz system clock     
#define TOGGLE_TIME_MS 500 // Delay between each toggle of led in ms.
#define T1_PRESCALER_A 256    // Timer 1 prescaler for task a)


// Include definition file(s)
#include <avr/interrupt.h>
#include <util/delay.h>



/*	Main program. */
int main( void )
{
	// Set PB5 and OC1A/PB1 as output.
	DDRB  = (1<<DDB5)|(1<<DDB1);
/*	Task 1
	Clear timer on compare match; top is then OCR1A. Toggle OC1A each time.
	Prescaler is 256, giving a range of 16000000/256 = 625000 ticks per second
	500 ms = 0.5s is thus 31250 */
	TCCR1A = (1<<COM1A0);
	TCCR1B = (1<<CS12)|(1<<CS10)|(1<<WGM12);
	// 31250, order to avoid overflow/truncation in compiler calculations: 
	OCR1A =  (((F_CPU / T1_PRESCALER_A) * TOGGLE_TIME_MS) / 1000 ); 
	TIMSK1 = (1<<OCIE1A);  // enable output compare interrupt
	sei();
	 
	// Wait for input/button to be pressed for change to mode 2. PB7 Xplained. PB0 on Arduino
	do { } while ( PINB & (1 << PINB0) );    
	cli();
	
/*	Task 2    
	8bit fast PWM inverting mode (256 steps). Set OC1A on Compare Match, clear at TOP. 
	Prescale by 8. 16MHz / (256*256)  = 244 Hz. */
	DDRB  |= (1<<DDB2);  // OC1B/PB2 pin as output also
	TCCR1A  = (1<<COM1B1)|(1<<COM1B0)|(1<<COM1A1)|(1<<COM1A0)|(1<<WGM10); 
	TCCR1B  = (1<<CS11)|(1<<WGM12);
//	Enable timer 1 overflow to increase duty cycle periodically. Use oc for sw pwm
	TIMSK1 = (1<<OCIE1A)|(1<<TOIE1);
	TIFR1 |= (1<<TOV1);  // clear timer overflow flag
	sei();

/*	Main loop is empty, but code for changing duty cycle is included and commented away. */

/*	Endless loop. Increases the duty cycle each PWM_DELAY_MS millisecond. 
	Delay in ms between each increase of duty cycle is 1000ms/16 = 62.5ms */
// 	#define PWM_DELAY_MS 63
// 	enum direction {DOWN=0, UP} count_direction;    
// 	uint8_t pwm_value[] = {0,1,2,3,5,7,10,15,22,31,44,63,90,127,180,255};
// 	uint8_t i = 0;
// 	count_direction = UP;

	do {
//   		OCR1A = pwm_value[i];
// //  		OCR1A++;
//  		OCR1B = pwm_value[15-i];
//  		_delay_ms(PWM_DELAY_MS);
// 		if(count_direction == UP)
// 		{
// 			i++;
// 			if (i >=15 ) {
// 				count_direction = DOWN;
// 			}
// 		} else {
// 			i--;
// 			if (i == 0 ) {
// 				count_direction = UP;
// 			}							
// 		}
	} while(1);
}


/*	The compare match interrupt could also be used for increasing the duty cycle
	which would not block the main loop and only be run when needed. It needs to 
	be adapted to the prescaler. This interrupt code assumes 8x prescaler, i.e
	8*256*1us ~= 2ms between each. */
ISR(TIMER1_OVF_vect)
{
	static uint8_t count=0;
	count++;
	if(count >= 64) {
		count = 0;
		OCR1A++;
		OCR1B--;
	}
	PINB |= (1<<PINB5);
}


/*	Timer1 compare interrupt used to toggle or software pwm on PB5/LED.*/
ISR(TIMER1_COMPA_vect)
{
	PINB |= (1<<PINB5);
}