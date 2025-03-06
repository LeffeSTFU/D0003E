/*
 * manager.c
 *
 * Created: 05/03/2025 12:45:41
 *  Author: alber
 */ 

#include "manager.h"

void joystickMove(Manager *manager, int arg) {
	if (checkIfFalling(manager)) 
	{
		return;
	}
	
	if (!((PINB >> 7) & 1)) //down 
	{
		ASYNC(manager->currentPulse, &decFreq, 0);
		if (!manager->moreDown) 
		{
			manager->moreDown = 1;
			AFTER(CONT_DELAY, manager, &contInput, 0);
		}
	}
	else if (!((PINB >> 6) & 1)) //up
	{
		ASYNC(manager->currentPulse, &incFreq, 0);
		if (!manager->moreUp) 
		{
			manager->moreUp = 1;
			AFTER(CONT_DELAY, manager, &contInput, 1);
		}
	}
	else if (!((PINB >> 4) & 1) && manager->jitterCounter == 0) //in
	{
		if(manager->currentPulse->freq == 0)
		{
			ASYNC(manager->currentPulse, &loadFreq, 0);
			manager->jitterCounter = 1;
			AFTER(CONT_DELAY, manager, &buttonJitterCounter, 0);
		} else 
		{
			ASYNC(manager->currentPulse, &saveFreq, 0);
			manager->jitterCounter = 1;
			AFTER(CONT_DELAY, manager, &buttonJitterCounter, 0);
		}
		
	}
	else if (!((PINE >> 2) & 1)) //left
	{
		ASYNC(manager, &selectPos, 0);
	}
	else if (!((PINE >> 3) & 1)) //right
	{
		ASYNC(manager, &selectPos, 1);
	}
	
	return;
}

void selectPos(Manager *manager, int pos) {
	if (pos) {
		manager->currentPulse = manager->rightPulse;
	}
	else {
		manager->currentPulse = manager->leftPulse;
	}
	return;
}

int checkIfFalling(Manager *manager) {
	if (manager->currentPulse->fallingEdgeDetect) {
		if(((PINB >> 7) & 1) || ((PINB >> 6) & 1)){
			manager->currentPulse->fallingEdgeDetect = 0;
			return 1;
		}
	}
	return 0;
}
void contInput(Manager *manager, int joystick) {
	manager->moreUp = 0;
	manager->moreDown = 0;
	
	if (joystick && !((PINB >> 6) & 1)) {
		manager->currentPulse->fallingEdgeDetect = 1;
		ASYNC(manager->currentPulse, &incFreq, 0);
	}
	else if (!joystick && !((PINB >> 7) & 1)) {
		manager->currentPulse->fallingEdgeDetect = 1;
		ASYNC(manager->currentPulse, &decFreq, 0);
	}
	return;
}
void buttonJitterCounter(Manager *manager, int arg) {
	manager->jitterCounter = 0;
	return;
}

void start(Manager *manager) {
	ASYNC(manager->leftPulse->gui, &printFreq, 0);
	ASYNC(manager->rightPulse->gui, &printFreq, 400);
}