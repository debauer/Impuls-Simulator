extern byte gpioSetPin(volatile byte *port, byte pin, byte value);
extern byte gpioSetPort(volatile byte *port,byte value);
extern byte gpioConfPort(volatile byte *port, byte conf);
extern byte gpioConfPin(volatile byte *port, byte pin, byte conf);