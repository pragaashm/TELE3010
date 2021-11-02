/*
 * oppgave_2.c
 *
 * Created: 08-Mar-20 10:50:58 PM
 * Author : praga
 * Creating a PWM with an 8-bit timer and LED (Timer0)
 */ 

#define F_CPU 16000 //Set frequency 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


double dCycle = 0; //define Cycle variable

int main(void)
{
	DDRD = (1 << PORTD6); // OC0A as output pin
	
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 <WGM01); // Compare output mode, Fast PMW 
	TIMSK0 = (1 << TOIE0); // Sets interrupt flag when value overflows
	
	OCR0A = (dCycle/100.0)*255; // Represents amount of time on
	
	sei(); // External interrupts
	
	TCCR0B = (1 << CS00); // Start the timer
	
	while(1)
	{
		_delay_ms(100); //Set delay
		
		//Increase dCycle by 10%. Resets when it hits 100
		dCycle += 10;
		
		if(dCycle > 100)
		{
			dCycle = 0;
		}
		
	}
}

ISR(TIMER0_OVF_vect)
{
	OCR0A = (dCycle/100.0)*255; // Not necessary, but can make the PWM dynamic (ex. change dCycle mid-program).

}