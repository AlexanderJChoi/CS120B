/*
 * achoi035_lab2_part1.c
 *
 * Created: 4/3/2019 10:11:55 AM
 * Author : ucrcse
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

