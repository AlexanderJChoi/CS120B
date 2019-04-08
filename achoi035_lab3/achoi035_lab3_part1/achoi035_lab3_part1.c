/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail:
 *	Lab Section: 26
 *	Assignment: Lab 3  Exercise 1
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

// Bit-access function
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k) {
	return ((x & (0x01 << k)) != 0);
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char tempA = 0x00, tempB = 0x00, tempC = 0x00;
	
    /* Replace with your application code */
    while (1) 
    {
		tempA = PINA;
		tempB = PINB;
		tempC = 0;
		
		for(char i = 0; i < 8; i++) {
			tempC += (GetBit(tempA, i) + GetBit(tempB, i));
		}
			
		PORTC = tempC;
    }
}

