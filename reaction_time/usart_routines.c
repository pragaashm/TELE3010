/*****************************************************************************
 *  Mikroprosessorsystemer                                                   *
 *  Labøving 8                                                               *
 *  Høgskolen i Sør-Trøndelag - Rolf Kristian Snilsberg                      *
 *                                                                           *
 *  Device: ATmega2560 in STK600                                             *
 *****************************************************************************
 */

/*** Usart routines file. ***/


//	Includes.
#include <avr/interrupt.h>
#include "usart_routines.h"


/*	Initialize UART with tx enabled. UBRR is defined in the header file.*/
void USART_TX_Init(uint16_t baud_value)
{
	/* Set the baud rate */
	UBRR0 = baud_value;
	
	/* Enable UART receiver */
	UCSR0B = (1<<TXEN0);
	//Default frame format is 8,1,N
	return;
}


/*	Transmit data. Waits for last transmission to complete and is thus blocking.*/
void USART_Transmit( char data )
{
	while (!(UCSR0A & (1<<UDRE0)));  // Wait for empty transmit buffer                
	UDR0 = data;                   // Start transmission
}


/*	Transmit a string. Waits for last transmission to complete then outputs 
	characters from the string until NULL character (\0) is encountered.*/
void USART_Transmit_String( char *data )
{
	while (*data != '\0' ) {
		while (!(UCSR0A & (1<<UDRE0)));  // Wait for empty transmit buffer                
		UDR0 = *data;                   // Start transmission
// 		USART_Transmit(*data);
		data++;
	}
}

