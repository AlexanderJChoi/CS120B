/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: ALexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 11  prelim
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include "keypad.h"
#include "io.c"


int main(void)
{
    unsigned char x;
    DDRB = 0xFF; PORTB = 0x00; // PORTB set to output, outputs init 0s
    DDRC = 0xF0; PORTC = 0x0F; // PC7..4 outputs init 0s, PC3..0 inputs init 1s
    while(1) {
	    x = GetKeypadKey();
	    switch (x) {
		    case '\0': PORTB = 0x1F; break; // All 5 LEDs on
		    case '1': PORTB = 0x01; break; // hex equivalent
		    case '2': PORTB = 0x02; break;
			case '3': PORTB = 0x03; break;
			case '4': PORTB = 0x04; break;
			case '5': PORTB = 0x05; break;
			case '6': PORTB = 0x06; break;
			case '7': PORTB = 0x07; break;
			case '8': PORTB = 0x08; break;
			case '9': PORTB = 0x09; break;
			case 'A': PORTB = 0x0A; break;
			case 'B': PORTB = 0x0B; break;
			case 'C': PORTB = 0x0C; break;
		    case 'D': PORTB = 0x0D; break;
		    case '*': PORTB = 0x0E; break;
		    case '0': PORTB = 0x00; break;
		    case '#': PORTB = 0x0F; break;
		    default: PORTB = 0x1B; break; // Should never occur. Middle LED off.
	    }
    }

}

