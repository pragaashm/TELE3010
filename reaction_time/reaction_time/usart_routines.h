/*****************************************************************************
 *  Mikroprosessorsystemer                                                   *
 *  Labøving 8                                                               *
 *  Høgskolen i Sør-Trøndelag - Rolf Kristian Snilsberg                      *
 *                                                                           *
 *  Device: ATmega2560 in STK600                                             *
 *****************************************************************************
 */

/*	Defines */
#define BAUD_RATE 9600UL
#define BAUD_VALUE F_CPU/(16UL*BAUD_RATE) - 1


/*	Prototypes */
void USART_TX_Init(uint16_t baud_value);
void USART_Transmit( char data );
void USART_Transmit_String( char *data );


