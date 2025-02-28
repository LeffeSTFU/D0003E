/*
 * CFile1.c
 *
 * Created: 18/02/2025 11:06:31
 *  Author: alber
 */ 

#include "portManager.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>


void joystickMove(PortManager *port){	// Joystick interrupt ends up here, each case is for a movement of the joystick
	PulseGenerator *currPulse = selectPos(port);
	if(port->isPressed){
		return;
	}
	
	if (!((PINB >> 7) & 1)){    // Down
		ASYNC(currPulse, &decFreq, 0);
		if (!port->isPressed){
			port->isPressed = 1;
			AFTER(CONT_REPEAT_DELAY_STICK, port, holdPin, 0);
		}
	}

	if (!((PINB >> 6) & 1)){    // Up
		ASYNC(currPulse, &incFreq, 0);
		if (!port->isPressed){
			port->isPressed = 1;
			AFTER(CONT_REPEAT_DELAY_STICK, port, holdPin, 0);
		}
	}

	if (!((PINE >> 2) & 1)){    // Left
		port->targetPulsePos = 0;
		ASYNC(currPulse, selectPos, 0);
	}
	if (!((PINE >> 3) & 1)){    // Right
		port->targetPulsePos = 4;
		ASYNC(currPulse, selectPos, 0);
	}
	
	if (!((PINB >> 4) & 1)){    // In
		if ((currPulse->currentFreq == 0) && (currPulse->saveBool)){
			ASYNC(currPulse, &loadFreq, 0);
			} else {
			ASYNC(currPulse, &saveFreq, 0);
		}
	}
	return;
}


PulseGenerator* selectPos(PortManager* port){	// Selects wanted pulse generator object
	PulseGenerator *currPulse;
	if (port->targetPulsePos == 0){
		currPulse = port->leftPulse;
	}
	else{
		currPulse = port->rightPulse;
	}
	return currPulse;
}


void holdPin(PortManager* port) {
	PulseGenerator* currPulse = selectPos(port);
	
	if((!((PINB >> 7) & 1)) && port->isPressed){ // Down 
		ASYNC(currPulse, &decFreq, 0);
		AFTER(CONT_REPEAT_DELAY_HOLD, port, holdPin, 0);
	}
	else if((!((PINB >> 6) & 1)) && port->isPressed) { // Up
		ASYNC(currPulse, &incFreq, 0);
		AFTER(CONT_REPEAT_DELAY_HOLD, port, holdPin, 0);
	} else{
		port->isPressed = 0;
	}

}


void start(PortManager *portman, int arg){	// Prints initial values of pulse generators on the screen
	ASYNC(portman->leftPulse, &startDisplay, 0);
	ASYNC(portman->rightPulse, &startDisplay, 0);
}