/*
 * Lab4.c
 *
 * Created: 17/02/2025 14:22:07
 * Author : alber
 */ 

#include "portManager.h"
#include "GUI.h"
#include "tinytimber.h"
#include "pulseGenerator.h"
#include "pulse.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <avr/interrupt.h>

void boostClk(void){
	CLKPR = 0x80;
	CLKPR = 0x00;
}

void initPinsNsuch(void){
	// PortB (DOWN,UP,CENTER) Enabled
	 PORTB = (1<<PB7) | (1<<PB6) | (1<<PB4);
	 
	 // PortE (RIGHT,LEFT) Enabled
	 PORTE = (1<<PE3) | (1<<PE2);
	 
	 // External Interrupt Mask Register
	 EIMSK = (1<<PCIE1) | (1<<PCIE0);
	 
	 // Pin Change Mask Register for DOWN,UP,CENTER
	 PCMSK1 = (1<<PCINT15)| (1<<PCINT14) | (1<<PCINT12);

	 // Pin Change Mask Register for RIGHT and LEFT
	 PCMSK0 = (1<<PCINT3) | (1<<PCINT2);
	 
	 DDRE = (1<<DDE6) | (1<<DDE4); // Turn on ports (Credits to my boy Spiffler #1 Limpus technician)
	 
	 // External async, Bias 1/3, Duty cycle 1/4, Set port mask for 25 segments
	 LCDCRB = (1<<LCDCS) | (0<<LCD2B) | (1<<LCDMUX0) | (1<<LCDMUX1) | (1<<LCDPM0) | (1<<LCDPM1) | (1<<LCDPM2);

	 // Prescaler = 16, clock divider = 8
	 LCDFRR = (1<<LCDCD0) | (1<<LCDCD1) | (1<<LCDCD2);

	 // Set maximum voltage 3.35V
	 LCDCCR = (1<<LCDCC0) | (1<<LCDCC1) | (1<<LCDCC2) | (1<<LCDCC3);

	 // LCD enabled, Low power waveform
	 LCDCRA = (1<<LCDEN) | (1<<LCDAB);
}

int main(void)
{
    /* Replace with your application code */
	boostClk();
	initPinsNsuch();
	
	
	static GUI gui = initGUI();	// The main GUI object
	static Pulse pulse = initPulse();
	static PulseGenerator leftPulse = initPulseGenerator(0, 0, 4, 0, false, &pulse);	// Left pulse generator
    static PulseGenerator rightPulse = initPulseGenerator(0, 0, 6, 4, false, &pulse);	// Right pulse generator
	static PortManager portMan = initportManager(&leftPulse, &rightPulse, 0, 0, 0);	// The portmanager
	
	INSTALL(&portMan, &joystickMove, IRQ_PCINT0); //interrupt for left and right
	INSTALL(&portMan, &joystickMove, IRQ_PCINT1); //interrupt for up, down and center
	
	return TINYTIMBER(&portMan, &start, 0);	// Start tinytimber, we just init the screen from the start method
	
}

