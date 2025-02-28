/*
 * IncFile1.h
 *
 * Created: 18/02/2025 11:03:58
 *  Author: alber
 */ 

#ifndef PULSEGENERATOR_H
#define PULSEGENERATOR_H

#define CONT_REPEAT_DELAY_HOLD MSEC(150)
#define CONT_REPEAT_DELAY_STICK MSEC(400)

#include "tinytimber.h"
#include "pulse.h"
#include "GUI.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>

typedef struct {
	Object super;
	int currentFreq;
	int savedFreq;
	int bitOut;
	int pos;
	bool saveBool;
	Pulse pulse;
} PulseGenerator;

#define initPulseGenerator(currentFreqIn, savedFreqIn, bitOutIn, posIn, saveBoolIn, pulseIn)\
	        {initObject(), currentFreqIn, savedFreqIn, bitOutIn, posIn, saveBoolIn, pulseIn}

void incFreq(PulseGenerator* self);
void decFreq(PulseGenerator* self);
void saveFreq(PulseGenerator* self);
void loadFreq(PulseGenerator* self);
void signalOutput(PulseGenerator* self);
void startDisplay(PulseGenerator* self);

#endif /* PULSEGENERATOR_H */