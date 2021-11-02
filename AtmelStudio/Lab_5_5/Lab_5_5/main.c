#define F_CPU 16e6
#define BAUDRATE 9600
#define UBRR_VALUE ((F_CPU / (BAUDRATE * 16UL)) - 1)
#include <avr/io.h>
#include <stdio.h>
void uart_init(void)
{
	UBRR0 = UBRR_VALUE;
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0); /* Enable RX and TX */
}
int uart_putchar(char c, FILE *stream)
{
	// if (c == '\n') {
	// uart_putchar('\r', stream);
	// }
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}
int uart_getchar(FILE *stream)
{
	loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
	return UDR0;
}
int main(void)

	uart_init();
	FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
	FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
	stdout = &uart_output;
	stdin = &uart_input;
	puts("Hello world!\r\n");
	while(1) {
		input = getchar();
		printf("%c", input);
	}
	// return 0;
}