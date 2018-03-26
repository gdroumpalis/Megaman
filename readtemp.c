#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{

	DDRB &= ~(1 << PINA0);
	DDRD = 0xff;
	ADCSRA = 0x8f;
	ADMUX = 0X40;

	sei();

	ADCSRA |= (1 << ADSC);

	while (1)
	{
		PORTD = ADCL;
		ADCSRA |= (1 << ADSC);
		_delay_ms(100);
	}

	return 0;
}

// ISR(ADC_vect)
// {

// 	PORTD = ADCL;
// 	ADCSRA |= (1 << ADSC);
// }