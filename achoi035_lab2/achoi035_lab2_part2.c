/*
 * Alexander Choi, achoi035@ucr.edu
 * Lab Section 26
 *
 * Lab 2, Exercise 2
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work. 
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	
	unsigned char tempA_0 = 0x00;
	unsigned char tempA_1 = 0x00;
	unsigned char tempA_2 = 0x00;
	unsigned char tempA_3 = 0x00;
	
	unsigned char tempC = 0x00;
	
    while (1) 
    {
		tempA_0 = (PINA & 0x01);
		tempA_1 = (PINA & 0x02) >> 1;
		tempA_2 = (PINA & 0x04) >> 2;
		tempA_3 = (PINA & 0x08) >> 3;
		
		tempC = 4 - (tempA_0 + tempA_1 + tempA_2 + tempA_3);
		
		PORTC = tempC;
    }
}

