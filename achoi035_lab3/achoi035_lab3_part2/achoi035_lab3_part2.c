/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail:
 *	Lab Section: 26
 *	Assignment: Lab 3  Exercise 2
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
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char fuelLevel = 0x00, ledOut = 0x00;
    /* Replace with your application code */
    while (1) 
    {
		fuelLevel = PINA & 0x0F;
		ledOut = 0;
		ledOut = SetBit(ledOut, 6, 1);
		
		switch (fuelLevel)
		{
		case 15:
		case 14:
		case 13:
			ledOut = SetBit(ledOut, 0, 1);
		case 12:
		case 11:
		case 10:
			ledOut = SetBit(ledOut, 1, 1);
		case 9:
		case 8:
		case 7:
			ledOut = SetBit(ledOut, 2, 1);
		case 6:
		case 5:
			ledOut = SetBit(ledOut, 3, 1);
			ledOut = SetBit(ledOut, 6, 0);
		case 4:
		case 3:
			ledOut = SetBit(ledOut, 4, 1);
		case 2:
		case 1:
			ledOut = SetBit(ledOut, 5, 1);
		case 0:
			break;
		default:
			break;
		}
		
		PORTC = ledOut;
    }
}

