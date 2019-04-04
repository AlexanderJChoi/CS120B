/*
 * Alexander Choi, achoi035@ucr.edu
 * Lab Section 26
 *
 * Lab 2, Exercise 1
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work. 
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned char tempA_0 = 0x00;
	unsigned char tempA_1 = 0x00;
	unsigned char tempB = 0x00;
    while (1) 
    {
		tempA_0 = (PINA & 0x01);
		tempA_1 = (PINA & 0x02) >> 1;
		
		if((tempA_0 == 0x01) && (tempA_1 == 0x00)) {
			tempB = 0x01;
		} else {
			tempB = 0x00;
		}
		
		PORTB = tempB;
    }
}

