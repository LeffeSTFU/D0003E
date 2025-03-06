/*
 * pulseGenerator.c
 *
 * Created: 05/03/2025 12:49:36
 *  Author: alber
 */ 

#include "pulseGenerator.h"

#define HERTZ USEC(500000 / self->freq) //Delay time for different freq
#define GUI_VAR ((self->pos)*100 + self->freq)	//Value sent for calls to print freq

void incFreq(PulseGenerator *self, int arg) {
	if (self->freq == 0) {
		self->state = 1;
		ASYNC(self, &outputFreq, 0);
	}
	if (self->freq < 99) {
		self->freq++;
		ASYNC(self->gui, &printFreq, GUI_VAR);
		
		if (self->fallingEdgeDetect) {
			AFTER(CONT_REPEAT_DELAY, self, &incFreq, 0);
		}
	}
}
void decFreq(PulseGenerator *self, int arg) {
	if (self->freq > 0) {
		self->freq--;
		ASYNC(self->gui, &printFreq, GUI_VAR);
		if (self->fallingEdgeDetect) {
			AFTER(CONT_REPEAT_DELAY, self, &decFreq, 0);
		}
		if (self->freq == 0) {
			self->state = 0;
		}
	}
	return;
}
void loadFreq(PulseGenerator *self, int arg) {
	self->freq = self->savedFreq;
	if (self->freq > 0) {
		self->state = 1;
		ASYNC(self, &outputFreq, 0);
		ASYNC(self->gui, &printFreq, GUI_VAR); // kan typ göras i outputFreq, vill man göra såhär????????????????????????????????????????????????????????????????????????????????????????
	}
	return;
}
void saveFreq(PulseGenerator *self, int arg) {
	self->savedFreq = self->freq;
	self->freq = 0;
	self->state = 0;
	ASYNC(self->gui, &printFreq, GUI_VAR);
	return;
}
void outputFreq(PulseGenerator *self, int arg) {
	if (self->state) {
		ASYNC(self->pulse, &togglePulse, self->pin);
		AFTER(HERTZ, self, &outputFreq, 0);
	}
	else {
		ASYNC(self->pulse, &offPulse, self->pin);
	}
	return;
}