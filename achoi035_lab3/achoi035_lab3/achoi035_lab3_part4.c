/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail:
 *	Lab Section: 26
 *	Assignment: Lab 3  Exercise 4
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>


int main(void)
{
	
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char input = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		input = PINA;
		
		PORTB = (input >> 4);
		PORTC = (input << 4);
    }
}

