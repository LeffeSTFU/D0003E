/*
 * manager.h
 *
 * Created: 05/03/2025 12:50:23
 *  Author: alber
 */ 

#include "TinyTimber.h"
#include "pulseGenerator.h"

#ifndef MANAGER_H_
#define MANAGER_H_

#define CONT_DELAY MSEC(400)

typedef struct {
	Object super;
	PulseGenerator *leftPulse;
	PulseGenerator *rightPulse;
	PulseGenerator *currentPulse;
	int jitterCounter;
	int moreUp;
	int moreDown;
} Manager;
	
#define initManager(leftPulseIn, rightPulseIn) {initObject(), leftPulseIn, rightPulseIn, leftPulseIn, 0, 0, 0}
	
void joystickMove(Manager *manager, int arg);
void selectPos(Manager *manager, int pos);
void start(Manager *manager);
int checkIfFalling(Manager *manager);
void contInput(Manager *manager, int arg);
void buttonJitterCounter(Manager *manager, int arg);




#endif /* MANAGER_H_ */