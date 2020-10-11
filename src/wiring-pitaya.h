#ifndef WIRING_PITAYA_H_
#define WIRING_PITAYA_H_

#include "gpio.h"

// Pin modes

#define	INPUT			 0
#define	OUTPUT			 1
#define	PWM_OUTPUT		 2
#define	GPIO_CLOCK		 3
#define	SOFT_PWM_OUTPUT		 4
#define	SOFT_TONE_OUTPUT	 5
#define	PWM_TONE_OUTPUT		 6

#define	LOW			 0
#define	HIGH			 1

/* #ifdef __cplusplus */
/* extern "C" { */
/* #endif */

// Core functions

extern void wiringPitayaVersion	(int *major, int *minor) ;
extern int  wiringPitayaSetup       (void) ;
extern int  wiringPitayaSetupSys    (void) ;
extern int  wiringPitayaSetupGpio   (void) ;
extern int  wiringPitayaSetupPhys   (void) ;

extern          void pinMode             (int pin, int mode) ;
extern          void digitalWrite        (int pin, int value) ;


// Schedulling priority

extern int piHiPri (const int pri) ;

// Extras from arduino land

extern void         delay             (unsigned int howLong) ;
extern void         delayMicroseconds (unsigned int howLong) ;


/* #ifdef __cplusplus */
/* } */
/* #endif */

#endif
