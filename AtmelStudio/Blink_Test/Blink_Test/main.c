/*
 * Blink_Test.c
 *
 * Created: 15-Jan-20 12:51:11 PM
 * Author : praga
 */ 

 
 #define F_CPU 16000000L // Specify oscillator frequency
 #include <avr/io.h>
 #include <util/delay.h>
 
 int main(void)
 {
	 DDRB |= 0B00100000; // configure pin 7 of PORTB as output (digital pin 13 on the Arduino Mega2560)
	 
	 while(1)
	 {
		 PORTB |= 0B00100000; // set 7th bit to HIGH
		 _delay_ms(1000);
		 PORTB = 0B11011111; // set 7th bit to LOW
		 _delay_ms(1000);
	 }
 }