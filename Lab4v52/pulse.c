/*
 * pulse.c
 *
 * Created: 05/03/2025 12:49:45
 *  Author: alber
 */ 
 #include "pulse.h"
 
 void togglePulse(Pulse *self, int pin){
	 PORTE ^= (1<<pin);
	 return;
 }
 
 void onPulse(Pulse *self, int pin){
	 PORTE |= (1<<pin);
	 return;
 }
 
 void offPulse(Pulse *self, int pin){
	 PORTE &= ~(1<<pin);
	 return;
 }