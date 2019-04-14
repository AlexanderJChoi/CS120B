/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: Alexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 4  Exercise 1
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>

enum Toggle_States {T_SMStart, T_wait_1, T_switch_1,  T_wait_2, T_switch_2} ToggleState;
	unsigned char led0 = 0x00, led1 = 0x00;
	
void TickFct_Toggle() {
	unsigned char button = PINA & 0x01;
	
	
	switch (ToggleState) { //actions
		case  T_SMStart:
			led0 = 0x01;
			led1 = 0x00;
			break;
		case T_switch_1:
			led0 = 0x00;
			led1 = 0x01;
			break;
		case T_switch_2:
			led0 = 0x01;
			led1 = 0x00;
			break;
	}

	switch (ToggleState) { //transitions
		case T_SMStart:
		ToggleState = T_wait_1;
		break;
		case T_wait_1:
		if (button) {
			ToggleState = T_switch_1;
		}
		break;
		case T_switch_1:
		if (!button) {
			ToggleState = T_wait_2;
		}
		break;
		case T_wait_2:
		if (button) {
			ToggleState = T_switch_2;
		}
		break;
		case T_switch_2:
		if (!button) {
			ToggleState = T_wait_1;
		}
		break;
		default:
		ToggleState = T_SMStart;
	}
	PORTB = led0 | (led1 << 1);
}
	
int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	
	
    /* Replace with your application code */
    while (1) 
    {
		TickFct_Toggle();
    }
}

