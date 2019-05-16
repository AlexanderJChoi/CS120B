/*	Partner 1 Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Partner 2 Name & E-mail: ALexander Yin, ayin005@ucr.edu
 *	Lab Section: 26
 *	Assignment: Lab 11  prelim
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit.h"
#include "timer.h"
#include "keypad.h"
#include "io.c"
#include <stdio.h>

//--------Find GCD function --------------------------------------------------
unsigned long int findGCD(unsigned long int a, unsigned long int b)
{
	unsigned long int c;
	while(1){
		c = a%b;
		if(c==0){return b;}
		a = b;
b = c;
	}
	return 0;
}
//--------End find GCD function ----------------------------------------------

//--------Task scheduler data structure---------------------------------------
// Struct for Tasks represent a running process in our simple real-time operating system.
typedef struct _task {
	/*Tasks should have members that include: state, period,
		a measurement of elapsed time, and a function pointer.*/
	signed char state; //Task's current state
	unsigned long int period; //Task period
	unsigned long int elapsedTime; //Time elapsed since last task tick
	int (*TickFct)(int); //Task tick function
} task;

//--------End Task scheduler data structure-----------------------------------

//--------Shared Variables----------------------------------------------------
unsigned char key_pressed = '\0';

//--------End Shared Variables------------------------------------------------

//--------User defined FSMs---------------------------------------------------
//Enumeration of states.
enum Key_States {key_read};
	
int keyTick(int state) {
	switch (state) {
		default:
			state = key_read;
	}
	
	switch (state) {
		case key_read:
			key_pressed = GetKeypadKey();
			break;
	}
	return state;
}

enum LED_States {LED_off, LED_num, LED_letter, LED_symb};
	
int LEDTick(int state) {
	switch(state) {
		case LED_off:
			if(key_pressed >= 48 && key_pressed <= 57) {
				state = LED_num;
			} else if(key_pressed >= 65 && key_pressed <= 68) {
				state = LED_letter;
			} else if(key_pressed == 0) {
				state = LED_off;
			} else {
				state = LED_symb;
			}
			break;
		case LED_num:
			if(key_pressed >= 48 && key_pressed <= 57) {
				state = LED_num;
			} else {
				state = LED_off;
			}
			break;
		case LED_letter:
			if(key_pressed >= 65 && key_pressed <= 68) {
				state = LED_letter;
			} else {
				state = LED_off;
			}
			break;
		case LED_symb:
			if(!(key_pressed >= 48 && key_pressed <= 57) && !(key_pressed >= 65 && key_pressed <= 68) && key_pressed != 0) {
				state = LED_symb;
			} else {
				state = LED_off;
			}
			break;
		default:
			state = LED_off;
	}
	
	switch(state) {
		case LED_num:
			PORTB = key_pressed - 48;
			break;
		case LED_letter:
			PORTB = key_pressed - 65 + 10;
			break;
		case LED_symb:
			PORTB = (key_pressed == 42) ? 0x0E : 0x0F;
			break;
		default:
			PORTB = 0;
	}
	return state;
}

// --------END User defined FSMs-----------------------------------------------

// Implement scheduler code from PES.
int main()
{
// Set Data Direction Registers
DDRC = 0x00; PORTC = 0xFF;
DDRB = 0xFF; PORTB = 0x00;

// Period for the tasks
unsigned long int keySM_calc = 50;
unsigned long int LEDSM_calc = 50;

//Calculating GCD
unsigned long int tmpGCD = 1;
tmpGCD = findGCD(keySM_calc, LEDSM_calc);

//Greatest common divisor for all tasks or smallest time unit for tasks.
unsigned long int GCD = tmpGCD;

//Recalculate GCD periods for scheduler
unsigned long int keySM_period = keySM_calc/GCD;
unsigned long int LEDSM_period = LEDSM_calc/GCD;

//Declare an array of tasks 
static task key, LED;
task *tasks[] = { &key, &LED};
const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

// Keypad
key.state = -1;//Task initial state.
key.period = keySM_period;//Task Period.
key.elapsedTime = keySM_period;//Task current elapsed time.
key.TickFct = &keyTick;//Function pointer for the tick.
// LEDs
LED.state = -1;//Task initial state.
LED.period = LEDSM_period;//Task Period.
LED.elapsedTime = LEDSM_period;//Task current elapsed time.
LED.TickFct = &LEDTick;//Function pointer for the tick.

// Set the timer and turn it on
TimerSet(GCD);
TimerOn();

unsigned short i; // Scheduler for-loop iterator
while(1) {
	// Scheduler code
	for ( i = 0; i < numTasks; i++ ) {
		// Task is ready to tick
		if ( tasks[i]->elapsedTime == tasks[i]->period ) {
			// Setting next state for task
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			// Reset the elapsed time for next tick.
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 1;
	}
	while(!TimerFlag) ;
	TimerFlag = 0;
}

// Error: Program should not exit!
return 0;
}
