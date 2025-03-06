/*
 * display.c
 *
 * Created: 05/03/2025 15:23:59
 *  Author: alber
 */ 
#include "display.h"

uint16_t arr[10] = {0x1551, 0x0110, 0x11e1, 0x11b1, 0x05b0, 0x14b1, 0x14f1, 0x1110, 0x15f1, 0x15b1};


void writeChar(char ch, int pos){
	uint8_t nibbles[4]; // Space for bits for each part of the number display
	uint16_t arrValue = arr[9-(57-ch)];	// saves the ascii value that ch represents
	
	for(uint8_t i = 0; i < 4; i++){	// loops and saves all the 4 sets of nibbles into the correct spots in the array
		nibbles[i] = arrValue & 0xf; // "and"s all the bits into the array
		arrValue = arrValue >> 4;
	}
	
	if(pos >= 0 && pos <= 5){	// General opening for choosing which pos to place numbers in
		if(pos == 0){	// for pos 0:
			LCDDR0		= LCDDR0 & ~(0xf); // clear all registers by "and"ing (~(0xf) (same as 0x0))
			LCDDR5		= LCDDR5 & ~(0xf);
			LCDDR10		= LCDDR10 & ~(0xf);
			LCDDR15		= LCDDR15 & ~(0xf);
			
			LCDDR0		= LCDDR0 | nibbles[3]; // or in all of the new data and turn on the correct LCD segments
			LCDDR5		= LCDDR5 | nibbles[2];
			LCDDR10		= LCDDR10 | nibbles[1];
			LCDDR15		= LCDDR15 | nibbles[0];
		}
		
		if(pos == 1){	// for pos 1:
			LCDDR0		= LCDDR0 & ~(0xf0); // clear all registers (same as 0x0)
			LCDDR5		= LCDDR5 & ~(0xf0);
			LCDDR10		= LCDDR10 & ~(0xf0);
			LCDDR15		= LCDDR15 & ~(0xf0);
			
			LCDDR0		= LCDDR0 | nibbles[3]<<4; // or in all of the new data
			LCDDR5		= LCDDR5 | nibbles[2]<<4; // shifted in to place on pos 1 (done on all odd number segments)
			LCDDR10		= LCDDR10 | nibbles[1]<<4;
			LCDDR15		= LCDDR15 | nibbles[0]<<4;
		}
		
		if(pos == 2){
			LCDDR1		= LCDDR1 & ~(0xf); // clear all registers (~(0xf) same as 0x0)
			LCDDR6		= LCDDR6 & ~(0xf);
			LCDDR11		= LCDDR11 & ~(0xf);
			LCDDR16		= LCDDR16 & ~(0xf);
			
			LCDDR1		= LCDDR1 | nibbles[3]; // or in all of the new data
			LCDDR6		= LCDDR6 | nibbles[2];
			LCDDR11		= LCDDR11 | nibbles[1];
			LCDDR16		= LCDDR16 | nibbles[0];
		}
		
		if(pos == 3){
			LCDDR1		= LCDDR1 & ~(0xf0); // clear all registers (same as 0x0)
			LCDDR6		= LCDDR6 & ~(0xf0);
			LCDDR11		= LCDDR11 & ~(0xf0);
			LCDDR16		= LCDDR16 & ~(0xf0);
			
			LCDDR1		= LCDDR1 | nibbles[3]<<4; // or in all of the new data
			LCDDR6		= LCDDR6 | nibbles[2]<<4;
			LCDDR11		= LCDDR11 | nibbles[1]<<4;
			LCDDR16		= LCDDR16 | nibbles[0]<<4;
		}
		
		if(pos == 4){
			LCDDR2		= LCDDR2 & ~(0xf); // clear all registers (~(0xf) same as 0x0)
			LCDDR7		= LCDDR7 & ~(0xf);
			LCDDR12		= LCDDR12 & ~(0xf);
			LCDDR17		= LCDDR17 & ~(0xf);
			
			LCDDR2		= LCDDR2 | nibbles[3]; // or in all of the new data
			LCDDR7		= LCDDR7 | nibbles[2];
			LCDDR12		= LCDDR12 | nibbles[1];
			LCDDR17		= LCDDR17 | nibbles[0];
		}
		
		if(pos == 5){
			LCDDR2		= LCDDR2 & ~(0xf0); // clear all registers (same as 0x0)
			LCDDR7		= LCDDR7 & ~(0xf0);
			LCDDR12		= LCDDR12 & ~(0xf0);
			LCDDR17		= LCDDR17 & ~(0xf0);
			
			LCDDR2		= LCDDR2 | nibbles[3]<<4; // or in all of the new data
			LCDDR7		= LCDDR7 | nibbles[2]<<4;
			LCDDR12		= LCDDR12 | nibbles[1]<<4;
			LCDDR17		= LCDDR17 | nibbles[0]<<4;
		}
		
	}
	
}


void printAt(long num, int pos) {	// Prints the current set frequency at the correct position from a given pulse generator
	int posNext = pos;
	writeChar( (num % 100) / 10 + '0', pos);
	posNext++;
	writeChar( num % 10 + '0', posNext);
}