/*
 * lab_adc_uart.c
 *
 * Created: 11.02.2019 15:40:39
 * Author : rksni
 */ 

#define F_CPU 16000000UL
#define USART_BAUDRATE 9600  // desired baud rate
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)  // UBRR value


/******************************|Includes|********************************/
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
/***********************************************************************/

/************************|function prototypes|**************************/
static int usart_putchar( char data,  FILE *stream );
void USART_init(uint16_t ubrr_value);
void ADC_init(void);
/***********************************************************************/

static FILE mystdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE); // for printf to work

int main(void)
{
	USART_init(UBRR_VALUE);
	stdout = &mystdout;              // to make printf work
	
	ADC_init();	

	do { // endless loop
		ADCSRA |= (1<<ADSC);  // Start adc conversion.
		do {} while (ADCSRA & (1<<ADSC));  // wait for it to finish
		printf("ADC data = %4u\r",ADC);   // prints out ADC value to USART
		_delay_ms(100);
	} while(1);

}


/***************************************************************************/
static int  usart_putchar(char data,  FILE *stream) {
	while ((UCSR0A & (1 << UDRE0)) == 0) {}; // Wait for empty transmit buffer
	UDR0 = data;
	return 0;                       // Start transmission
}


/********************************|usart init|*******************************/
void USART_init(uint16_t ubrr_value)
{
	UBRR0 = ubrr_value;	             // set baud rate to 9600
	UCSR0C = (3<<UCSZ00);            // 8 bit data
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);  // enable transmitter, reciever and interrupt
}

/*!	ADC initialization. Prescaler 128x, resulting in 125kHz adc clock @ 16MHz.
	ADC0 input. AVCC as reference. Result left-adjusted.
 */
void ADC_init(void)
{
	ADMUX  = (1<<REFS0); // ADC0 single ended input. AVCC as reference.
	DIDR0 |= (1<<ADC0D); // digital input buffer disable, saves power.
	ADCSRA = (1<<ADEN)|(7<<ADPS0);  // 128x prescaler gives 125kHz adc clock @ 16MHz system
}

