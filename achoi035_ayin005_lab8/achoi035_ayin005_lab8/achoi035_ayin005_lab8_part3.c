/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: ALexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 8  Exercise 3
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>


void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit enables auto-triggering. Since we are
	//        in Free Running Mode, a new conversion will trigger whenever
	//        the previous conversion completes.
}

enum State {read } state;
unsigned char out_B, out_D;

void tick() {
	unsigned short x = ADC;
	
	
	switch(state) {
		case read:
			state = read;
			break;
	}
	
	switch(state) {
		case read:
			out_B = x >= 63 ? 1 : 0; 
			break;
	}
	
	PORTB = out_B;
	PORTD = out_D;
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	ADC_init();
	
	out_B = 0;
	out_D = 0;
	state = read;
    /* Replace with your application code */
    while (1) 
    {
		tick();
    }
}

