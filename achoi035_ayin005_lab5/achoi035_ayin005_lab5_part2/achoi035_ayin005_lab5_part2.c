/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: Alexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 5  Exercise 2
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>

enum States {S_init, S_wait, S_inc, S_inc2, S_dec, S_dec2, S_reset} state;
unsigned char display;

void tick() {
	unsigned char button_inc = ~PINA & 0x01;
	unsigned char button_dec = (~PINA & 0x02);
	
	switch (state) { //state transitions
		case S_init:
			state = S_wait;
			break;
		case S_wait:
			if(button_inc && button_dec) {
				state = S_reset;
			} else if(button_inc) {
				state = S_inc;
			} else if(button_dec) {
				state = S_dec;
			} else {
				state = S_wait;
			}
			break;
		case S_inc:
			if(button_inc && button_dec) {
				state = S_reset;
			} else {
				state = S_inc2;
			}
			break;
		case S_inc2:
			if(button_inc && button_dec) {
				state = S_reset;
			} else if (!button_inc) {
				state = S_wait;
			} else {
				state = S_inc2;
			}
			break;
		case S_dec:
			if(button_inc && button_dec) {
				state = S_reset;
			} else {
				state = S_dec2;
			}
			break;
		case S_dec2:
			if(button_inc && button_dec) {
				state = S_reset;
			} else if (!button_dec) {
				state = S_wait;
			} else {
				state = S_dec2;
			}
			break;
		case S_reset:
			if(button_dec || button_inc) {
				state = S_reset;
			} else {
				state = S_wait;
			}
			break;
		default:
			state = S_init;
			break;
	}
	
	switch (state) { //state actions
		case S_init:
			display = 0x07;
			break;
		case S_inc:
			if(display < 9) {
				display++;
			}
			break;
		case S_dec:
			if(display > 0) {
				display--;
			}
			break;
		case S_reset:
			display = 0;
			break;
		default:
		break;
	}
	
	PORTB = display;
	PORTC = state;
}

int main(void)
{
    /* Replace with your application code */
    display = 0x07;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	state = S_init;
	
    while (1)  {
		tick();
    }
}

