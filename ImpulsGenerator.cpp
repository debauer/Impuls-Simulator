/*
 * ImpulsGenerator.cpp
 *
 * Created: 04.04.2013 19:03:02
 *  Author: debauer
 */ 

#define VAR_DEFINITION
#include "global.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/setbaud.h>
#include <avr/interrupt.h>
#include "module/timer.h"
#include "module/gpio.h"
#undef VAR_DEFINITION

// Timer Pointer der Impulse
uint8_t timer[8];
// Impulse
uint32_t impulsAbstand[8]; // in 1ms
uint8_t impulsRandom[8];
uint8_t impulsState[8];
uint8_t impulsleange[8]; // in 1ms
uint8_t doppelImpulsAbstand[8];
uint16_t doppelImpulsFaktor[8];		// in 0.001 - range 64-0.001
uint16_t doppelImpulsFaktorRest[8];

uint8_t portAdr[8];
uint8_t portPin[8];

#include <avr/io.h>

void gpioSetPinAdapter(uint8_t port, byte pin, byte value){
	if(port == 'D'){
		gpioSetPin(&PORTD, pin, value);	
	}else{
		gpioSetPin(&PORTB, pin, value);	
	}
}


int main(void)
{
	static uint8_t i;
	
	DDRB = 0xFF;
	DDRC = 0xFF;
	timerInit();			// Timerzellen Init
	INT_GLOBAL_ON;			// Alle Interupts scharf machen
	
	portAdr[0] = 'D';
	portPin[0] = 3;
	portAdr[1] = 'D';
	portPin[1] = 4;
	portAdr[2] = 'D';
	portPin[2] = 5;
	portAdr[3] = 'D';
	portPin[3] = 6;
	portAdr[4] = 'D';
	portPin[4] = 7;
	portAdr[5] = 'B';
	portPin[5] = 0;
	portAdr[6] = 'B';
	portPin[6] = 1;
	portAdr[7] = 'B';
	portPin[7] = 2;
	
	gpioSetPinAdapter(portAdr[0], 3, 1);
	gpioSetPinAdapter(portAdr[0], 3, 1);
		
	for(i=0;i<8;i++){
		impulsState[i] = 0;
		impulsRandom[i] = 0;		// nicht random
		timerSet(i, 1000);
		impulsAbstand[i] = 300;	// 1s
		impulsleange[i] = 20;		// 20ms
		doppelImpulsAbstand[i] = 20;// 100ms
		doppelImpulsFaktor[i] = 1500;	// keine doppel Impulse
	}
	
	//impulsAbstand[0] = 100;	// 1s
	//impulsAbstand[1] = 120;	// 1s	
	//impulsAbstand[2] = 140;	// 1s
	//impulsAbstand[3] = 160;	// 1s
	//impulsAbstand[4] = 180;	// 1s
	//impulsAbstand[5] = 200;	// 1s
	//impulsAbstand[6] = 220;	// 1s
	//impulsAbstand[7] = 240;// 1s
		
    while(1)
    {
		if(timerNull(i)){
			timerSet(i, impulsAbstand[i]);
		}
		for(i=0;i<8;i++){	
			if(timerNull(i)){
				impulsState[i] = 0;	 // Hard Reset
			}
			switch(impulsState[i]){
				default:
				case 0:	//wait
					// ausgang ausschalten
					gpioSetPinAdapter(portAdr[i], portPin[i], 0);
					if(timerNull(i)){
						impulsState[i] = 1;
						timerSet(i+8, impulsleange[i]);
					}						
					break;
				case 1: // HIGH
					gpioSetPinAdapter(portAdr[i], portPin[i], 1);
					// ausgang anschalten
					if(timerNull(i+8)){
						if(doppelImpulsFaktor[i] == 1000){
							impulsState[i] = 0;	
						}else{
							doppelImpulsFaktorRest[i] += doppelImpulsFaktor[i];
							impulsState[i] = 2;
							timerSet(i+8, doppelImpulsAbstand[i]);
						}												
					}
					break;
				case 2: // LOW
					gpioSetPinAdapter(portAdr[i], portPin[i], 0);
					if(timerNull(i+8)){
						if(doppelImpulsFaktorRest[i] > 1000){
							impulsState[i] = 3;
							timerSet(i+8, impulsleange[i]);
						}else{
							impulsState[i] = 0;
						}
					}					
				case 3: // doppel High
					gpioSetPinAdapter(portAdr[i], portPin[i], 1);
					if(timerNull(i+8)){
						impulsState[i] = 2;	
						doppelImpulsFaktorRest[i] -= 1000;
						timerSet(i+8, doppelImpulsAbstand[i]);
					}
			}				
				
		}			
    }
}

ISR (TIMER0_OVF_vect)
{
	timerStart(); // HW-Timer neu starten
	timerDec();   // Alle Timerzellen Decrementieren
}