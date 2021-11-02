/*****************************************************************************
 *  Mikroprosessorsystemer                                                   *
 *  Labøving reaksjonstidsmåler                                              *
 *  NTNU Insitutt for elektrofag og fornybar energi                          *
 *  Rolf Kristian Snilsberg                                                  *
 *  Device: ATmega328P in  Xplained mini                                     *
 *****************************************************************************
 */

/* Defines*/
#define F_CPU 16000000UL
#define LEDS_ON  0x00   // LEDs active low, this value turns all on
#define LEDS_OFF 0xFF   // LEDs active low, this value turns all off

// Includes
#include <avr/io.h>
#include <util/delay.h>
