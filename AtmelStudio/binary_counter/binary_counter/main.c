#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void delay_ms (uint16_t ms);
void delay_us (uint16_t us);

/*Global Variables Declarations*/
unsigned char COUNTER_1 = 0x03;
unsigned char COUNTER_2 = 0x00;
int num = 0;

int main(void)
{
	
	DDRD = 0xFC;  // LED's connected to PD2,PD3,PD4,PD5,PD6,PD7  -- PD2 is the LSB
	DDRB = 0x03;  // LED's connected to PB0,PB1                  -- PB1 is the MSB
	
	
	while(1)
	{


		num++;
		delay_ms(100); //wait 200 ms


		PORTD &= 0b00000011;  // clear bits 7:2
		PORTD |= num<<2;

		PORTB &= 0b11111100;
		PORTB |= num>>6;


	}
	return 0;
}



void delay_ms (uint16_t ms) {
	uint16_t i;
	for (i = 0; i < ms; i++)
	_delay_ms(1);
	
}
void delay_us (uint16_t us) {
	uint16_t i;
	
	for (i = 0; i < us; i++)
	_delay_us(1);
}