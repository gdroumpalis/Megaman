#include <avr/io.h>
#include "util/delay.h"
#include "avr/interrupt.h"

#define	F_CPU	1000000

void usart_init()
{
	UBRRH = 0;
	UBRRL =51;
	UCSRB|= (1<<RXEN)|(1<<TXEN);
	UCSRC |= (1 << URSEL)|(3<<UCSZ0);
}

void usart_data_transmit(unsigned char data )
{
	while ( !( UCSRA & (1<<UDRE)) );
	UDR = data;
	_delay_ms(100);
}

void usart_string_transmit(char *string)
{
	while(*string)
	{
		usart_data_transmit(*string++);
	}
}

int main(void)
{
    	//DDRD = 0XFF;
	/* Replace with your application code */
	usart_init();
	//sei();
	
	while (1)
	{

		usart_string_transmit("Hello\n");
		/*Transmits string to PC*/

		usart_data_transmit(0x0d);
		
	}
}