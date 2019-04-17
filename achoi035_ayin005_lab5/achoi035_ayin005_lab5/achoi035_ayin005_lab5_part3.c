/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: Alexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 5  Exercise 3
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

enum State {patternA_0, patternA_1, patternA_2, patternB_0, patternB_1, patternB_2} state;
unsigned short count;
unsigned char lights;
	
void tock() {
	unsigned char button = ~PINA & 0x01;
	count++;
	
	switch(state) {
		case patternA_0:
			lights = 0x01;
			break;
		case patternA_1:
		case patternA_2:
			if(count == 0xFFFF) {
				if(lights == 0x80) {
					lights = 0x01;
				} else {
					lights <<= 1;
				}
				count = 0;
			}
			break;
		case patternB_0:
			lights = 0b01010101;
			break;
		case patternB_1:
		case patternB_2:
			if(count == 0xFFFF) {
				lights <<= 1;
				if(!(lights & 0x80)) {
					lights |= 0x01;
				} 
				count = 0;
			}
			break;
		default:
			break;
	}
	
	switch(state) {
		case patternA_0:
			state = patternA_1;
			break;
		case patternA_1:
			if(button) {
				state = patternA_1;
			} else {
				state = patternA_2;
			}
			break;
		case patternA_2:
			if(button) {
				state = patternB_0;
			} else {
				state = patternA_2;
			}
			break;
		case patternB_0:
			state = patternB_1;
			break;
		case patternB_1:
			if(button) {
				state = patternB_1;
			} else {
				state = patternB_2;
			}
			break;
		case patternB_2:
			if(button) {
				state = patternA_0;
			} else {
				state = patternB_2;
			}
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
	count = 0;
	lights = 0;
	
    while (1) 
    {
		tock();
    }
}

