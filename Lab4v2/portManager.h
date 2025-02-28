/*
 * IncFile1.h
 *
 * Created: 18/02/2025 11:06:44
 *  Author: alber
 */ 


#ifndef PORTMANAGER_H
#define PORTMANAGER_H

#define CONT_REPEAT_DELAY_HOLD MSEC(150)
#define CONT_REPEAT_DELAY_STICK MSEC(400)

#include "tinytimber.h"
#include "pulseGenerator.h"
#include "tinytimber.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>


typedef struct {
	Object super;
	PulseGenerator *leftPulse;
	PulseGenerator *rightPulse;
	int targetPulsePos;
	bool isPressed;
	Msg prevAfter;
	
} PortManager;

#define initportManager(leftPulseIn, rightPulseIn, targetPulsePosIn, isPressedIn, prevAfterIn)\
		 {initObject(), leftPulseIn, rightPulseIn, targetPulsePosIn, isPressedIn, prevAfterIn}

void joystickMove(PortManager* port);
PulseGenerator* selectPos(PortManager* port);
void holdPin(PortManager* port);
void start(PortManager* port, int arg);
#endif /* PORTMANAGER_H */