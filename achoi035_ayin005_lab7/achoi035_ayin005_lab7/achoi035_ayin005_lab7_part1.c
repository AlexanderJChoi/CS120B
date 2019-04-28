/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: ALexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 7  Exercise 1
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "io.c"



volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1 ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks

void TimerOn() {
	// AVR timer/counter controller register TCCR1
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	// bit2bit1bit0=011: pre-scaler /64
	// 00001011: 0x0B
	// SO, 8 MHz clock or 8,000,000 /64 = 125,000 ticks/s
	// Thus, TCNT1 register will count at 125,000 ticks/s

	// AVR output compare register OCR1A.
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	// We want a 1 ms tick. 0.001 s * 125,000 ticks/s = 125
	// So when TCNT1 register equals 125,
	// 1 ms has passed. Thus, we compare to 125.
	// AVR timer interrupt mask register
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	//Initialize avr counter
	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	// TimerISR will be called every _avr_timer_cntcurr milliseconds

	//Enable global interrupts
	SREG |= 0x80; // 0x80: 1000000
}

void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}

void TimerISR() {
	TimerFlag = 1;
}

// In our approach, the C programmer does not touch this ISR, but rather TimerISR()
ISR(TIMER1_COMPA_vect) {
	// CPU automatically calls when TCNT1 == OCR1 (every 1 ms per TimerOn settings)
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

// Set TimerISR() to tick every M ms
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

enum State {wait, inc, dec, clear} state;
unsigned char count;

void tick() { 
	unsigned char button_inc = ~PINA & 0x01;
	unsigned char button_dec = ~PINA & 0x02;
	
	switch(state) { //transitions
		case wait: 
			if(button_inc && button_dec) {
				state = clear;
			} else if(button_inc) {
				TimerOn();
				state = inc;
			} else if(button_dec) {
				TimerOn();
				state = dec;
			} else {
				state = wait;
			}
			break;
		case inc:
			if(button_inc && button_dec) {
				TimerOff();
				state = clear;
			} else if(button_inc) {
				state = inc;
			} else {
				TimerOff();
				state = wait;
			}
			break;
		case dec:
			if(button_inc && button_dec) {
				TimerOff();
				state = clear;
			} else if(button_dec) {
				state = dec;
			} else {
				TimerOff();
				state = wait;
			}
			break;
		case clear:
			if(button_inc && button_dec) {
				state = clear;
			} else {
				state = wait;
			}
			break;
	}
	
	switch(state) {
		case wait:
			TimerFlag = 1;
			break;
		case inc:
			if(TimerFlag) {
				if(count < 9) {
					count++;
					LCD_Cursor(1);
					LCD_WriteData(count + '0');
				}
				TimerFlag = 0;
			}
			break;
		case dec:
			if(TimerFlag) {
				if(count > 0) {
					count --;
					LCD_Cursor(1);
					LCD_WriteData(count + '0');
				}
				TimerFlag = 0;
			}
			break;
		case clear:
			count = 0;
			LCD_Cursor(1);
			LCD_WriteData(count + '0');
			break;
	}
	
}

int main(void)
{
    /* Replace with your application code */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	count = 0;

	TimerSet(1000);
	LCD_init();

	
    while (1) 
    {
		tick();
    }
}

