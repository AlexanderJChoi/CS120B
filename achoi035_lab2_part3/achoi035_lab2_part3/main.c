/*
 * achoi035_lab2_part3.c
 *
 * Created: 4/3/2019 10:36:13 AM
 * Author : ucrcse
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
		
		tempC = (tempC & 0xF0) | ((4 - (tempA_0 + tempA_1 + tempA_2 + tempA_3)) & 0x0F);
		
		if((tempC & 0x0F) == 0) {
			tempC = (tempC & 0x7F) | 0x80;
		} else {
			tempC = (tempC & 0x7F) | 0x00;
		}
		
		PORTC = (PORTC & 0x70) | (tempC & 0x8F);
	}
}

