#include <avr/io.h>
#include "../global.h"

unsigned int timerTicks;
unsigned int softTimer[TIMER_ANZAHL];
unsigned int softTimerNull[TIMER_ANZAHL];

#ifdef ATMEGA
void timerInit(){
	TCNT0  = TIMER_START;
	TCCR0B = 0x05;
	TIMSK0 |= 0x01;
}
#endif

#ifdef ATMEGA
void timerStart(){
	TCNT0  = TIMER_START;
}
#endif

void timerSet(byte nr, int count){
	softTimer[nr] = count;
	softTimerNull[nr] = false;
}
void timerSetNullAll(){
	byte i;
	for(i = 0; i<TIMER_ANZAHL; i++){
		if(softTimer[i] == 0){
			softTimer[i] = 0;
			softTimerNull[i] = true;
		}
	}
}
bool timerNull(byte nr){
	return softTimerNull[nr];
}
void timerDec(){
	byte i;
	for(i = 0; i<TIMER_ANZAHL; i++){
		if(softTimer[i] != 0){
			softTimer[i]--;
			if(softTimer[i] == 0){
				softTimerNull[i] = true;
			}
		}
	}
}