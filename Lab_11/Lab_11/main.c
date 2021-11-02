/*
 * Lab_11.c
 *
 * Created: 15-Apr-20 1:47:44 PM
 * Author : praga
 */ 

#include <avr/io.h>


int main(void)
{
    volatile int8_t int8var = -200; // overflow - warning
    volatile uint8_t uint8var = 100;
    volatile int16_t int16var = -5000;
    volatile uint16_t uint16var = 2000;
    volatile int int_var = 1000;
    volatile int32_t int32var = 2000*5000;//10000000UL;// overflow in expressionwarning
    int32var = 2000/5000*200;
    int16var = int8var * uint8var;
    int8var = int8var / uint8var;
    int8var++;
    uint16var++;
    int16var++;
    int32var++;
    volatile float floatvar = 3.5;
    volatile float floatvar2 = 4.7;
    floatvar = floatvar * uint8var;
    floatvar = floatvar/floatvar2;
	
    while (1)
    {
	    asm("nop");
    }
}

