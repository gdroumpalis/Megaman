#include <avr/io.h>
#include "util/delay.h"
#include "avr/interrupt.h"
 
void usart_init()
{
	UBRRH = 0;
	UBRRL =51;
	UCSRB|= (1<<RXEN)|(1<<TXEN);
	UCSRC |= (1 << URSEL)|(3<<UCSZ0);
}

void usart_data_transmit(unsigned int data )
{
	while ( !( UCSRA & (1<<UDRE)) );
	UDR = data;
	_delay_ms(1000);
}
unsigned int i = 0;
int main(void)
{
	/* Replace with your application code */
	usart_init();
	//sei();
	
	while (1)
	{
		usart_data_transmit(i);
		/*Transmits string to PC*/

		usart_data_transmit(0x0d);
		i++;
	}
}