/* Name & E-mail: Alexander Choi, achoi035@ucr.edu
 *	Lab Section: 26
 *	Assignment: Final Project
 *	
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

#include <avr/io.h>
#include "nokia5110.h"
#include "nokia5110.c"

enum LCD_update {render} state;
unsigned char letter;
short x = 0;

unsigned char character[] = {0xF8, 0xF8, 0xF8, 0xF8, 0xF8};
unsigned char character2[] = {0xA8, 0x50, 0xA8, 0x50, 0xA8};
unsigned char character3[] = {0x88, 0x50, 0x20, 0x50, 0x88};
unsigned char character4[] = {0xF8, 0xA8, 0xA8, 0xA8, 0xF8};
unsigned char coin[] = {0xF8, 0x88, 0x88, 0x88, 0xF8};

unsigned char maze[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x01, 0xff, 0xff, 0xff, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x01, 0xff, 0xff, 0xff, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x18, 0x01, 0x80, 0x18, 0x01, 0xff, 0xff, 0xff, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x18, 0x01, 0x80, 0x18, 0x01, 0xff, 0xff, 0xff, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xff, 0xf8, 0x01, 0xff, 0xf8, 0x01, 0xff, 0xf8, 0x01, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xff, 0xf8, 0x01, 0xff, 0xf8, 0x01, 0xff, 0xf8, 0x01, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xff, 0xf8, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x18, 0x01, 0xff, 0xf8, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xff, 0xf8, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x18, 0x01, 0xff, 0xf8, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x0c,
	0xff, 0xfc, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x18, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xff, 0xfc, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x18, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x01, 0x80, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x0f, 0xff, 0xc0, 0x18, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xfc,
	0xc0, 0x0f, 0xff, 0xc0, 0x18, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xfc,
	0xc0, 0x0c, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x1f, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x18, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xfc,
	0xc0, 0x0c, 0x00, 0xc0, 0x1f, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x18, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xfc,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1a, 0xab, 0xaa, 0xba, 0xab, 0x80, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x18, 0x01, 0x80, 0x1d, 0x55, 0xd5, 0x5d, 0x55, 0x80, 0x18, 0x01, 0x80, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x0f, 0xff, 0xc0, 0x18, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x18, 0x01, 0x80, 0x1f, 0xff, 0x80, 0x0c,
	0xc0, 0x0f, 0xff, 0xc0, 0x18, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x80, 0x18, 0x01, 0x80, 0x1f, 0xff, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0f, 0xff, 0xff, 0xf8, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xf8, 0x01, 0x80, 0x0c,
	0xc0, 0x0f, 0xff, 0xff, 0xf8, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xf8, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0c,
	0xc0, 0x0f, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xf8, 0x01, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x0c,
	0xc0, 0x0f, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xf8, 0x01, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x1f, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xf8, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0c, 0x00, 0xc0, 0x1f, 0xff, 0x80, 0x1f, 0xff, 0xff, 0xf8, 0x01, 0x80, 0x18, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0xc0, 0x00, 0x01, 0x80, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x18, 0x01, 0x80, 0x0c,
	0xc0, 0x0f, 0xff, 0xff, 0xf8, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x0c,
	0xc0, 0x0f, 0xff, 0xff, 0xf8, 0x01, 0x80, 0x1f, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0x80, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc};
	

int LCD_updateTick(int state) {
	switch(state) {
		default:
			state = render;
	}
	
	switch(state) {
		case render:
			nokia_lcd_render();
			nokia_lcd_clear();
	}
	return state;
}

void LCD_drawImage(unsigned char * image, short pos_x, short pos_y, uint8_t size_x, uint8_t size_y) {
	
	uint8_t line_size = (size_x % 8 == 0) ? (size_x / 8) : (size_x / 8) + 1;
	uint8_t row, col;
	unsigned char bit;
	unsigned short tempX, tempY, tempI;
	
	for (row = (pos_y < 0) ? (pos_y * -1) : 0; row < size_y; row++) {
		tempY = pos_y + row;
		if((tempY < 48)) {
			for (col = (pos_x < 0) ? (pos_x * -1 / 8) : 0; col < line_size; col++ ) {
				tempI = row * line_size + col;
				for (bit = 0; bit < 8; bit++) {
					tempX = pos_x + (col * 8) + ( 7 - bit );
					if ( ((image[tempI] & (1 << bit))) && (tempX < 84)) {
						nokia_lcd_set_pixel(tempX, tempY, 1);
					}
				}
			}
		} else {
			break;
		}
	}
}


int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	state = render;
	letter = 'a';
	nokia_lcd_init();
	

	while (1)
	{
		unsigned char up = ~PINA & 0x01;
		unsigned char down = ~PINA & 0x02;
		if(up) {
			x++;
		} else if(down) {
			x--;
		}
		
		//nokia_lcd_set_pixel(x, 20, 1);
		LCD_drawImage(&(maze[0]), x, 0, 158, 158);
		
		state = LCD_updateTick(state);
	}
}

