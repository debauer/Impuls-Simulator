#ifdef VAR_DEFINITION
#define EXT
#else
#define EXT extern
#endif

#define BUFFERSIZEMAX 500

#define F_CPU 16000000UL
#define SCL_CLOCK  400000L
#define ATMEGA
#define ATMEGA328A

#define TCNT _SFR_MEM8(0x46)
#define TCCRB _SFR_MEM8(0x45)
#define TCCRA _SFR_MEM8(0x44)
#define TIMSK _SFR_MEM8(0x6E)

#define TIMER_ANZAHL 16
#define TIMER_START 0x64 // 10ms bei 16mhz/1024

#define STRING_TERMINIERUNG '#'


/*  Interrupts  */
EXT volatile unsigned char interupt;

#define	INT_GLOBAL_ON  sei();
#define	INT_GLOBAL_OFF cli();

/*  UART  */

#define UDR	_SFR_MEM8(0xC6)
//#define BAUD 9600UL
//#define BAUD 19200UL
#define BAUD 38400UL
//define BAUD 115200UL

#define UBRR_VAL ((F_CPU+BAUD*8)/(BAUD*16)-1)   // clever runden
#define BAUD_REAL (F_CPU/(16*(UBRR_VAL+1)))     // Reale Baudrate
#define BAUD_ERROR ((BAUD_REAL*1000)/BAUD)		// Fehler in Promille, 1000 = kein Fehler.

#if ((BAUD_ERROR<990) || (BAUD_ERROR>1010))
#error Systematischer Fehler der Baudrate groesser 1% und damit zu hoch!
#endif


/*  Definitionen  */

#define bool unsigned char
#define BOOL bool
#define byte unsigned char
#define BYTE byte
#define BUFFERSIZEMAX 500
#define IN 1
#define TRUE 1
#define true 1
#define OUT 0
#define FALSE 0
#define false 0
#define NULL 0