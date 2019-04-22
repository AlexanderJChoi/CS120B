/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: Alexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 5  Exercise 3
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

enum State {patternA_0, patternA_1, patternA_2} state;
unsigned char lights;
	
void tock() {
	unsigned char buttonAdvanceSequence = ~PINA & 0x01;
	
	switch(state) {
		case patternA_0:
			break;
		case patternA_1:
			break;
		case patternA_2:
			if(lights == 0x80) {
				lights = 0x01;
				} else {
				lights <<= 1;
			}
			break;
		default:
			break;
	}
	
	switch(state) {
		case patternA_0:
			if(buttonAdvanceSequence) {
				state = patternA_0;
			} else {
				state = patternA_1;
			}
			break;
		case patternA_1:
			if(buttonAdvanceSequence) {
				state = patternA_2;
			} else {
				state = patternA_1;
			}
			break;
		case patternA_2:
			state = patternA_0;
			break;
		default:
			break;
	}
	
	PORTB = lights;
}


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = patternA_0;
	lights = 0x01;
	
    while (1) 
    {
		tock();
    }
}

