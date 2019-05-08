/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: ALexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 10  Exercise 2
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "io.c"

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

enum THREE_LED_STATE {t_one, t_two, t_three} three_led_state;
enum BLINKLED_STATE {b_one, b_two} blink_led_state;
enum SPEAKER_STATE {s_on, s_off} speaker_state;
enum COMBO_STATE {write} combo_state;
unsigned char three_led_out, blink_led_out, speaker_out, b_out;
unsigned long three_led_time, blink_led_time, speaker_time, combo_time;

void three_led_tick() {
	switch(three_led_state) {
		case t_one:
			three_led_state = t_two;
			break;
		case t_two:
			three_led_state = t_three;
			break;
		case t_three:
			three_led_state = t_one;
			break;
		default:
			three_led_state = t_one;
	}
	
	switch(three_led_state) {
		case t_one:
			three_led_out = 0x01;
			break;
		case t_two:
			three_led_out = 0x02;
			break;
		case t_three:
			three_led_out = 0x04;
			break;
	}
}

void blink_led_tick() {
	switch(blink_led_state) {
		case b_one:
			blink_led_state = b_two;
			break;
		case b_two:
			blink_led_state = b_one;
			break;
		default:
			blink_led_state = b_one;
	}
	switch(blink_led_state) {
		case b_one:
			blink_led_out = 0x08;
			break;
		case b_two:
			blink_led_out = 0x00;
			break;
	}
}

void speaker_tick() {
	unsigned char button = ~PINA & 0x04;
	switch(speaker_state) {
		case s_on:
			speaker_state = s_off;
			break;
		case s_off:
			if(button) {
				speaker_state = s_on;
			} else {
				speaker_state = s_off;
			}
			break;
		default:
			speaker_state = s_on;
		
	}
	switch(speaker_state) {
		case s_on:
			speaker_out = 0x10;
			break;
		case s_off:
			speaker_out = 0;
			break;
	}
}

void combo_tick() {
	switch(combo_state) {
		case write:
		default:
			combo_state = write;
			
	}
	switch(combo_state) {
		case write:
			PORTB = three_led_out | blink_led_out | speaker_out;
	}
}


int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	
	three_led_out = 0;
	blink_led_out = 0;
	b_out = 0;
	speaker_out = 0;
	
	three_led_time = 0;
	blink_led_time = 0;
	combo_time = 0;
	speaker_time = 0;
	
	three_led_state = t_one;
	blink_led_state = b_one;
	speaker_state = s_on;
	combo_state = write;
	
	TimerSet(1);
	TimerOn();
	
    /* Replace with your application code */
    while (1) 
    {
		if(three_led_time >= 300) {
			three_led_tick();
			three_led_time = 0;
		}
		if(blink_led_time >= 1000) {
			blink_led_tick();
			blink_led_time = 0;
		}
		if(speaker_time >= 3) {
			speaker_tick();
			speaker_time = 0;
		}
		if(combo_time >= 1) {
			combo_tick();
			combo_time = 0;
		}
		while(!TimerFlag);
		TimerFlag = 0;
		three_led_time++;
		blink_led_time++;
		speaker_time++;
		combo_time++;
    }
}

