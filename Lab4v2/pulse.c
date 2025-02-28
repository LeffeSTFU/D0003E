/*
 * pulse.c
 *
 * Created: 27/02/2025 14:30:26
 *  Author: alber
 */ 

#include "pulse.h"

void setHigh(Pulse* self, int pin){	// sets pins to high
	if(pin == 4){
		PORTE |= (1<<4);
	}
	
	if(pin == 6){
		PORTE |= (1<<6);
	}
}


void setLow(Pulse* self, int pin){	// sets pins to low
	if(pin == 4){
		PORTE &= ~(1 << 4);
	}
	if(pin == 6){
		PORTE &= ~(1 << 6);
	}
}