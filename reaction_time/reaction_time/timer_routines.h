/*****************************************************************************
 *  Mikroprosessorsystemer                                                   *
 *  Labøving 8                                                               *
 *  Høgskolen i Sør-Trøndelag - Rolf Kristian Snilsberg                      *
 *                                                                           *
 *  Device: ATmega2560 in STK600                                             *
 *****************************************************************************
 */

/*** Timer routines header file. ***/
#include <avr/io.h>
#include <util/delay.h>

//	Prototypes
void Timer1_Init_Capture(void);
uint8_t wait_random_time(void);
uint16_t measure_reaction_time(void);

