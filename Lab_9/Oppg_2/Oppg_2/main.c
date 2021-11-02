/*
 * Oppg_2.c
 *
 * Created: 11-Mar-20 1:52:48 PM
 * Author : praga
 */ 

#define F_CPU 16000000 //16MHz
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Setting Input capture max value, Output compare max/min values.
#define ICR_MAX (long double)F_CPU/64/50 //5000
#define OCR_MIN ICR_MAX/54 //92
#define OCR_MAX ICR_MAX/9 //555

//setting variables. Turning off hardware access
volatile unsigned long adc_val=0;
volatile unsigned long counter=0;
unsigned long curr_adc=0;

//Creating counter for the servo
ISR (ADC_vect)
{
	adc_val += ADC;
	counter++;
}

int main(void)
{
	DDRB |= (1<<DDB1); //PD1 set as output
	
	ICR1 = ICR_MAX; //Setting max time between pulse
	OCR1A = OCR_MIN; //Generates interrupt after X time
	
	TCCR1A = (1 << COM1A1) | (1<<WGM11); //Set Timer1 control register A
	TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10); //Timer/Counter1 control register B
	
		
	ADMUX = (1 << REFS0); //Voltage reference set to 5V
	ADCSRA = (1 << ADEN)|(1 << ADATE)|(1 << ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Enabling and starting ADC converting
	//ADEN = Enable ADC|ADATE = Free running(Continuous conversion)|ADIE = Interrupts when conversion is complete|ADPS2/1/0 = Division factor enabled
	
	
	
	sei(); //Interrupt enabled
	
	ADCSRA |= (1<<ADSC); //Starting conversion
	

	while(1)
	{
		if(counter >= 500) //Checking counter
		{
			cli(); //Clear global interrupt (Avoid interrupts from occurring).
			
			unsigned long round_val = round(adc_val / counter); //Rounds to the nearest integer
			
			//Sets variables to 0
			adc_val=0;
			counter=0;
			
			if(abs(round_val - curr_adc) > 1) //Checks if the absolute value > 1
			{
				curr_adc = round_val; //Replace value
			}
			
			long double servo = OCR_MIN + ((long double)curr_adc * (OCR_MAX - OCR_MIN)/1024); //Adding and converting new servo value.
			
			OCR1A = (int)round(servo); //Moves servo to the given value
			
			sei(); //Enable interrupts
		}
	}
}	