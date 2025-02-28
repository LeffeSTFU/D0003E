/*
 * pulse.h
 *
 * Created: 27/02/2025 14:30:36
 *  Author: alber
 */ 

#include "tinytimber.h"
#include <avr/io.h>
#include <stdint.h>

#ifndef PULSE_H_
#define PULSE_H_

typedef struct {
	Object super;
} Pulse;

#define initPulse() {initObject()}


void setHigh(Pulse* self, int pin);
void setLow(Pulse* self, int pin);


#endif /* PULSE_H_ */