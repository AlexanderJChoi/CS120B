/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: Alexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 5  Exercise 0_0
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

int main(void)
{
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs
	while(1)
	{
		PORTB = 0x0F; // Writes port B's 8 pins with 00001111
	}
}
