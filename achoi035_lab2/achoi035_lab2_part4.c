/*
 * Alexander Choi, achoi035@ucr.edu
 * Lab Section 26
 *
 * Lab 2, Exercise 4
 * I acknowledge all content contained herein, excluding template or example
 * code, is my own original work. 
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
	
	unsigned char tempA = 0x00, tempB = 0x00, tempC = 0x00, tempD = 0x00;
	unsigned int tempSum = 0x00;
	
    while (1) 
    {
		tempA = PINA;
		tempB = PINB;
		tempC = PINC;
		tempSum = tempA + tempB + tempC;
		
		if(tempSum > 140) {
			tempD = tempD | 0x01;
		} else {
			tempD = tempD & 0xFE;
		}
		
		if(((tempA >= tempC) && (tempA - tempC > 80)) || ((tempC >= tempA) && (tempC - tempA > 80))) {
			tempD = tempD | 0x02;
		} else {
			tempD = tempD & 0xFD;
		}
		
		//We'll display a binary number on D7 ... D2. This number multiplied by 2 will be the approximate weight
		tempD = (tempD & 0x03) | (((tempSum) << 1) & 0x0FC);
		
		
		PORTD = tempD;
    }
}

