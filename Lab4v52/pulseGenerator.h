/*
 * pulseGenerator.h
 *
 * Created: 05/03/2025 12:50:46
 *  Author: alber
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <stdio.h>
#include "TinyTimber.h"
#include "pulse.h"
#include "GUI.h"

#ifndef PULSEGENERATOR_H_
#define PULSEGENERATOR_H_

#define CONT_REPEAT_DELAY MSEC(150)

typedef struct{
	Object Super;
	int freq;
	int state;
	int savedFreq;
	int fallingEdgeDetect;
	int pin;
	int pos;
	GUI *gui;
	Pulse *pulse;
}PulseGenerator;

#define initPulseGenerator(pinIn, posIn, guiIn, pulseIn)\
{initObject(),0, 0, 0, 0, pinIn, posIn, guiIn, pulseIn}
	
void incFreq(PulseGenerator *self, int arg);
void decFreq(PulseGenerator *self, int arg);
void loadFreq(PulseGenerator *self, int arg);
void saveFreq(PulseGenerator *self, int arg);
void outputFreq(PulseGenerator *self, int arg);

#endif /* PULSEGENERATOR_H_ */