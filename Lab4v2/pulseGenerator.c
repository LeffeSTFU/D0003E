/*
 * CFile1.c
 *
 * Created: 18/02/2025 11:03:48
 *  Author: alber
 */ 

#include "pulseGenerator.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>


void incFreq(PulseGenerator* self){	// Increases frequency
	if(self->currentFreq < 99){
		self->currentFreq += 1;
		printAt(self->pos, self->currentFreq);
	}
}


void decFreq(PulseGenerator* self){	// Decreases frequency
	if(self->currentFreq > 0){
		self->currentFreq -= 1;
		printAt(self->pos, self->currentFreq);
	}	
}


void saveFreq(PulseGenerator* self){	// Saves current frequency
	self->savedFreq = self->currentFreq;
	self->currentFreq = 0;
	self->saveBool = true;
	printAt(self->pos, self->currentFreq);
}


void loadFreq(PulseGenerator* self){	// Loads stored frequency
	self->currentFreq = self->savedFreq;
	self->saveBool = false;
	printAt(self->pos, self->currentFreq);
}


void signalOutput(PulseGenerator* self){	// Toggles pins on/off att desired frequency
	if(self->currentFreq == 0){
		ASYNC(&self->pulse, setLow, &self->bitOut);
	} else{
		volatile int waitCycles = 8000000 / (self->currentFreq * 2); // Calculation for the amount of cycles to wait before switching high/low depending on the wanted frequency (cycles = (CPU execution speed)/(2*wanted Frequency))
		ASYNC(&self->pulse, setHigh, &self->bitOut);
		
		AFTER(waitCycles, &self->pulse, setLow, &self->bitOut); // Set low after "time" cycles
		
		if(self->saveBool){ // Exits the infinite calls if the saveFreq method is called, from joystick interrupts

		} else {
			
		AFTER(waitCycles, self, signalOutput, 0); // run signalOutput again to start the pulse over again after waitCycles amount of cycles
			
		}
	}
}

void startDisplay(PulseGenerator* self){
	printAt(self->pos, self->currentFreq);
}