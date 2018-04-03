#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libfiles/uart.h>

#define degree_sysmbol 0xdf

void ADC_Init(){										
	DDRA = 0x00;	        /* Make ADC port as input */
	ADCSRA = 0x87;          /* Enable ADC, with freq/128  */
	ADMUX = 0x40;           /* Vref: Avcc, ADC channel: 0 */
}
void usart_init()
{
	UBRRH = 0;
	UBRRL =51;
	UCSRB|= (1<<RXEN)|(1<<TXEN);
	UCSRC |= (1 << URSEL)|(3<<UCSZ0);
}
int ADC_Read(char channel)							
{
	ADMUX = 0x40 | (channel & 0x07);   /* set input channel to read */
	ADCSRA |= (1<<ADSC);               /* Start ADC conversion */
	while (!(ADCSRA & (1<<ADIF)));     /* Wait until end of conversion by polling ADC interrupt flag */
	ADCSRA |= (1<<ADIF);               /* Clear interrupt flag */
	_delay_ms(1);                      /* Wait a little bit */
	return ADCW;                       /* Return ADC word */
}

void usart_data_transmit(unsigned char data )
{
	while ( !( UCSRA & (1<<UDRE)) );
	UDR = data;
	//_delay_ms(100);
}

void usart_string_transmit(char *string)
{
	while(*string)
	{
		usart_data_transmit(*string++);
	}
}

int main()
{
	char Temperature[10];
	float celsius;
    char buffer[20];
	ADC_Init();                 /* initialize ADC*/
	usart_init();
	while(1)
	{
	   
	   celsius = (ADC_Read(0)*4.88);
	   celsius = (celsius/10.00);

	   itoa(celsius,Temperature,10);
        usart_string_transmit(Temperature);
        usart_string_transmit("\n");
		/*Transmits string to PC*/

		usart_data_transmit(0x0d);
	   _delay_ms(80);
	   memset(Temperature,0,10);
	}
}