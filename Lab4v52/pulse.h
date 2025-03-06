/*
 * pulse.h
 *
 * Created: 05/03/2025 12:50:34
 *  Author: alber
 */ 

#include "TinyTimber.h"
#include <avr/io.h>
#include <stdint.h>

#ifndef PULSE_H_
#define PULSE_H_

typedef struct{
	Object super;
}Pulse;

#define initPulse(){initObject()}
void togglePulse(Pulse *self, int pin);
void onPulse(Pulse *self, int pin);
void offPulse(Pulse *self, int pin);


#endif /* PULSE_H_ */