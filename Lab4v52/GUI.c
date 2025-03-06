/*
 * GUI.c
 *
 * Created: 05/03/2025 12:46:16
 *  Author: alber
 */ 

#include "GUI.h"

void printFreq(GUI *gui, int arg) {
	int freq = arg%100;
	int pos = (arg-freq)/100;
	printAt(freq, pos);
	
	return;
}