/*
 * Oppg_1.c
 *
 * Created: 11-Mar-20 12:09:04 PM
 * Author : praga
 */ 

#define F_CPU 16000000 //Set frequency


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


void main(void)
{
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);        //NON Inverted PWM
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //External clock source on T1 pin. Fast PWM
	ICR1=4999;  //Top value, fPWM=50Hz /20ms between pulse
	DDRB |= (1 << DDB1);   //OC1A/PB1 as output
	
	while(1)
	{
		//OCR1A: Generate interrupts after X clock ticks
		OCR1A=97; //0 degree
		_delay_ms(1000);
		OCR1A=310;   //90 degree
		_delay_ms(1000);
		OCR1A=530;  //180 degree
		_delay_ms(1000);
	}
}