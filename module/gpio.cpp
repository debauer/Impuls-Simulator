#include <avr/io.h>
#include "../global.h"

#ifdef ATMEGA

byte gpioSetPin(volatile byte *port, byte pin, byte value){
	if(value == true){
		*port |= (1<<pin);	
	}else{
		*port &= ~(1<<pin);	
	}
}
byte gpioSetPort(volatile byte *port,byte value){
	*port = value;
}
byte gpioConfPort(volatile byte *port, byte conf){
	*port = conf;
}
byte gpioConfPin(volatile byte *port, byte pin, byte conf){
	*port = (conf<<pin);
}

#endif