/*
 * IncFile1.h
 *
 * Created: 18/02/2025 11:06:18
 *  Author: alber
 */ 

#ifndef GUI_H
#define GUI_H

#include "tinytimber.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>


typedef struct {
	Object super;
} GUI;

#define initGUI() {initObject()}

void(*writeAt)(char ch, int pos);
void printAt(int pos, int num);

#endif /* GUI_H */