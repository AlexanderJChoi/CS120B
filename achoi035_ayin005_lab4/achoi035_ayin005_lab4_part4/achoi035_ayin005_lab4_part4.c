/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: Alexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 4  Exercise 4
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */


#include <avr/io.h>
#define BUTTON_INSIDE 'i'
#define BUTTON_POUND_SIGN '#'
#define BUTTON_X 'x'
#define BUTTON_Y 'y'

enum State {S_init, S_wait, S_check, S_unlock, S_lock} state;
unsigned char lock;
unsigned char input;
unsigned char num_correct_inputs;
unsigned char passcode[] = "#y";

void tick() {
	unsigned char button_inside = (PINA & 0x80) >> 7,
					button_pound_sign = (PINA & 0x04) >> 2,
					button_Y = (PINA & 0x02) >> 1,
					button_X = PINA & 0x01;
					
	unsigned char check_input_still_pressed = (input == BUTTON_INSIDE && button_inside) || (input == BUTTON_POUND_SIGN && button_pound_sign) || (input == BUTTON_X && button_X) || (input == BUTTON_Y && button_Y),
					check_only_one_pressed = button_inside ^ button_pound_sign ^ button_X ^ button_Y,
					check_correct_input = input == passcode[num_correct_inputs],
					check_full_pass_entered = input == passcode[num_correct_inputs] && passcode[num_correct_inputs + 1] == '\0',
					check_door_is_locked = !lock;
	
	
	switch (state) { //action
		case S_init:
			lock = 0x00;
			input = 0x00;
			num_correct_inputs = 0x00;
			break;
		case S_wait:
			if(button_inside) {
				input = BUTTON_INSIDE;
			} else if(button_pound_sign) {
				input = BUTTON_POUND_SIGN;
			} else if(button_X) {
				input = BUTTON_X;
			} else if(button_Y) {
				input = BUTTON_Y;
			} else {
				input = '\0';
			}
			break;
		case S_check:
			if(check_input_still_pressed) {
				// do nothing until button is released
			} else {
				if(input == BUTTON_INSIDE) {
					// do nothing
				} else if(check_full_pass_entered) {
					// do nothing
				} else if(check_correct_input) {
					num_correct_inputs++;
				} else {
					num_correct_inputs = 0;
				}
			}
			break;
		case S_lock:
			lock = 0x00;
			num_correct_inputs = 0;
			break;
		case S_unlock:
			lock = 0x01;
			num_correct_inputs = 0;
			break;
		default:
			break;
	}
	
	switch (state) { //transition
		case S_init:
		case S_unlock:
		case S_lock:
			state = S_wait;
			break;
		case S_wait:
			if(check_only_one_pressed) {
				state = S_check;
			} else {
				state = S_wait;
			}
			break;
		case S_check:
			if(check_input_still_pressed) {
				state = S_check;
			} else {
				if(input == BUTTON_INSIDE) {
					state = S_lock;
				} else if(check_full_pass_entered) {
					if(check_door_is_locked) {
						state = S_unlock; 
					} else {
						state = S_lock;
					}
				} else {
					state = S_wait;
				}
			}
			break;
		default: 
			state = S_wait;
			break;
	}
	
	
	PORTB = lock;
}


int main(void)
{
    /* Replace with your application code */
	lock = 0x00;
	input = 0x00;
	num_correct_inputs = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = lock;
	state = S_init;
	
    while (1) 
    {
		tick();
    }
}

