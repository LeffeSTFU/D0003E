/*
 * GUI.h
 *
 * Created: 05/03/2025 12:49:56
 *  Author: alber
 */ 

#include "TinyTimber.h"
#include "display.h"
#include <avr/io.h>


#ifndef GUI_H_
#define GUI_H_

typedef struct{
	Object super;
}GUI;

#define initGUI(){initObject()}

void printFreq(GUI *gui, int arg);

#endif /* GUI_H_ */