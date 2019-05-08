/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: ALexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 9  Exercise 2
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>


// 0.954 hz is lowest frequency possible with this function,
// based on settings in PWM_on()
// Passing in 0 as the frequency will stop the speaker from generating sound
void set_PWM(double frequency) {
	static double current_frequency; // Keeps track of the currently set frequency
	// Will only update the registers when the frequency changes, otherwise allows
	// music to play uninterrupted.
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; } //stops timer/counter
		else { TCCR3B |= 0x03; } // resumes/continues timer/counters
		
		// prevents OCR3A from overflowing, using prescaler 64
		// 0.954 is smallest frequency that will not result in overflow
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		
		// prevents OCR0A from underflowing, using prescaler 64					// 31250 is largest frequency that will not result in underflow
		else if (frequency > 31250) { OCR3A = 0x0000; }
		
		// set OCR3A based on desired frequency
		else { OCR3A = (short)(8000000 / (128 * frequency)) - 1; }

		TCNT3 = 0; // resets counter
		current_frequency = frequency; // Updates the current frequency
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	// COM3A0: Toggle PB3 on compare match between counter and OCR0A
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	// WGM02: When counter (TCNT0) matches OCR0A, reset counter
	// CS01 & CS30: Set a prescaler of 64
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum State {stop_0, stop_1, play_0, play_1, up, down} state;
unsigned char i;

double sounds[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

void tick() {
	unsigned char buttonOn = ~PINA & 0x01, 
					buttonUp = (~PINA & 0x02) >> 1, 
					buttonDown = (~PINA & 0x04) >> 2;

	switch (state) {
		case stop_0: 
			if(buttonOn) {
				state = stop_0;
			} else {
				state = stop_1;
			}
			break;
		case stop_1:
			if(buttonOn) {
				state = play_0;
			} else {
				state = stop_1;
			}
			break;
		case play_0:
			if(buttonOn) {
				state = play_0;
			} else {
				state = play_1;
			}
			break;
		case play_1:
			if(buttonOn) {
				state = stop_0;
			} else if(buttonUp) {
				state = up;
				if (i < 7) {
					i++;
				}
			} else if(buttonDown) {
				state = down;
				if (i > 0) {
					i--;
				}
			}
			break;
		case up:
			if(buttonUp) {
				state = up;
			} else {
				state = play_0;
			}
			break;
		case down:
			if(buttonDown) {
				state = down;
			} else {
				state = play_0;
			}
			break;
		default:
			state = stop_0;
			break;
	}

	switch(state) {
		case stop_0:
		case stop_1:
			set_PWM(0);
			break;
		case play_0:
		case play_1:
		case up:
		case down:
			set_PWM(sounds[i]);
			break;
		default:
			set_PWM(0);
			break;
	}

}


int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	state = stop_0;
	i = 0;
	PWM_on();
	set_PWM(1);
	set_PWM(0);
	
	
    /* Replace with your application code */
    while (1) 
    {
		tick();
		//PORTC = state;
    }
}

