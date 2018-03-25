#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{

	//DDRB |= (1<<PINB0);
	DDRD = 0xff;
	ADCSRA = 0x8f;
	ADMUX = 0X40;

	sei();

	ADCSRA |= (1 << ADSC);

	while (1)
	{
		//_delay_ms(1000);
		//PORTB^=(1<<PINB0);
	}

	return 0;
}

ISR(ADC_vect)
{

	PORTD = ADCL;
	ADCSRA |= (1 << ADSC);

}