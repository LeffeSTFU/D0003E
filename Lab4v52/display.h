/*
 * display.h
 *
 * Created: 05/03/2025 15:24:11
 *  Author: alber
 */ 

#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#ifndef DISPLAY_H_
#define DISPLAY_H_

void WriteChar(char ch, int pos);

void printAt(long num, int pos);



#endif /* DISPLAY_H_ */