#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int tempC;
int readADC(char channel)
{
	ADMUX = (3 << REFS0) | (1 << ADLAR) | (channel << MUX0); // VREF=2.56V, 8-bit, channel #0 is on PA0
	_delay_us(10);											 // allow multiplexer to settle
	ADCSRA |= (1 << ADSC);									 // Start Conversion
	while (ADCSRA & (1 << ADSC));		 // wait for completion
	return ADCH; // 8-bit result because we use ADLAR
}
int main(void)
{
	DDRC = 0b11111111;
	DDRD = 0b11111111;

	ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS2);
	TIMSK = (1 << TOIE0); // enable timer overflow interrupt for Timer0
	TCNT0 = 0x00;		  // set timer0 counter initial value to 0
	TCCR0 = (1 << CS01);  // start timer0 with /8 prescaler
	sei();

	while (1)
	{
		temp = readADC(0)
	}

	return 0;
}
ISR(ADC_vect)
{

	PORTD = ADCL;
	ADCSRA |= (1 << ADSC);
}