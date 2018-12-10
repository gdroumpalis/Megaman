//**************************************************************//
//Microcontroller			:ATmega32
//System Clock				:8MHz 
//Project					:ATmega32 to PC Communication with LCD Display
//Software					:AVR Studio 4
//LCD Data Interfacing		:8-Bit
//USART Baud Rate			:9600
//USART Data Bits			:8
//USART Stop Bits			:1
//USART Mode				:Asynchronous Mode
//USART Parity				:No Parity   
//Author					:Arun Kumar Garg 
//							:ABLab Solutions
//							:www.ablab.in
//							:info@ablab.in
//Date						:1st January 2012
//**************************************************************//

#include<avr/io.h>
/*Includes io.h header file where all the Input/Output Registers and its Bits are defined for all AVR microcontrollers*/

#define	F_CPU	8000000
/*Defines a macro for the delay.h header file. F_CPU is the microcontroller frequency value for the delay.h header file. Default value of F_CPU in delay.h header file is 1000000(1MHz)*/

#include<util/delay.h>
/*Includes delay.h header file which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/

#define		LCD_DATA_PORT		PORTB
/*LCD_DATA_PORT is the microcontroller PORT Register to which the data pins of the LCD are connected. Here it is connected to PORTB*/

#define 	LCD_CONT_PORT		PORTC
/*LCD_CONT_PORT is the microcontroller PORT Register to which the control pins of the LCD are connected. Here it is connected to PORTC*/

#define 	LCD_RS 		PC0
/*LCD_RS is the microcontroller Port pin to which the RS pin of the LCD is connected. Here it is connected to PC0*/

#define 	LCD_RW 		PC1
/*LCD_RW is the microcontroller Port pin to which the RW pin of the LCD is connected. Here it is connected to PC1*/

#define 	LCD_EN 		PC2
/*LCD_EN is the microcontroller Port pin to which the EN pin of the LCD is connected. Here it is connected to PC2*/

/*Alphanumeric LCD Function Declarations*/
void lcd_data_write(char data);
void lcd_command_write( char command);
void lcd_init();
void lcd_string_write( char *string);

/*USART Function Declarations*/
void usart_init();
void usart_data_transmit(unsigned char data );
void usart_string_transmit(char *string);

int main(void)
{
	DDRB=0xff;
	/*All the 8 pins of PortB are declared output (data pins of LCD are connected)*/

	DDRC=0x07;
	/*PC0, PC1 and PC2 pins of PortC are declared output (control pins of LCD are connected)*/

	usart_init();
	/*USART initialization*/
	
	lcd_init();
	/*LCD initialization*/

	/*Start of infinite loop*/
	while(1)
	{
		usart_string_transmit("ABLab Solutions");
		/*Transmits string to PC*/

		usart_data_transmit(0x0d);
		/*Transmits Carriage return to PC for new line*/

		usart_string_transmit("www.ablab.in");
		/*Transmits string to PC*/

		usart_data_transmit(0x0d);
		/*Transmits Carriage return to PC for new line*/

		lcd_command_write(0x80);
		/*Cursor moves to 1st row 1st column*/

		lcd_string_write("ABLab Solutions");
		/*String is displayed in 1st row of LCD*/

		lcd_command_write(0xc0);
		/*Cursor moves to 2nd row 1st column*/

		lcd_string_write("www.ablab.in");
		/*String is displayed in 2nd row of LCD*/

		_delay_ms(500);
		/*Strings are transmitted and displayed with a time gap of 500ms*/
	}
}
/*End of program*/


/*USART Function Definitions*/
void usart_init()
{
	UBRRH = 0;
	UBRRL =51;
	UCSRB|= (1<<RXEN)|(1<<TXEN);
	UCSRC |= (1 << URSEL)|(3<<UCSZ0);
}


void usart_data_transmit(unsigned char data )
{
	while ( !( UCSRA & (1<<UDRE)) )
		;
	UDR = data;
	_delay_ms(1);
}


void usart_string_transmit(char *string)
{
	while(*string)
	{
		usart_data_transmit(*string++);
	}
}



/*Alphanumeric LCD Function Definitions*/
void lcd_data_write(char data)
{
	LCD_CONT_PORT=_BV(LCD_EN)|_BV(LCD_RS);
	LCD_DATA_PORT=data;
	_delay_ms(1);
	LCD_CONT_PORT=_BV(LCD_RS);
	_delay_ms(1);
}


void lcd_command_write(char command)
{
	LCD_CONT_PORT=_BV(LCD_EN);
	LCD_DATA_PORT=command;
	_delay_ms(1);
	LCD_CONT_PORT=0x00;
	_delay_ms(1);
}

void lcd_init()
{
	lcd_command_write(0x38);
	lcd_command_write(0x01);
	lcd_command_write(0x06);
	lcd_command_write(0x0e);	
}

void lcd_string_write(char *string)
{
	while (*string)
		lcd_data_write(*string++);
}


