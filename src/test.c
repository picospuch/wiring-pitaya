#include "wiring-pitaya.h"
#include "soft-pwm.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define RANGE		100
#define	NUM_LEDS	  2

int ledMap [NUM_LEDS] = { 0, 1 } ;

int values [NUM_LEDS] = { 25, 25 } ;

int main ()
{
  int i, j ;
  char buf [80] ;

  wiringPitayaSetup ()  ;

  for (i = 0; i < NUM_LEDS; ++i) {
    pinMode(ledMap[i], 0);
  }

  for (i = 0 ; i < NUM_LEDS ; ++i)
  {
    softPwmCreate (ledMap[i], 0, RANGE);
    printf ("%3d, %3d, %3d\n", i, ledMap[i], values[i]);
  }

  printf("Press any enter to breathe...");
  fgets (buf, 80, stdin) ;

  while (1) {
    for (i = 0 ; i < NUM_LEDS ; ++i) {
      for (j = 0 ; j <= 100 ; ++j) {
        softPwmWrite (ledMap [i], j) ;
        delay (10) ;
      }
      for (j = 100 ; j >=0 ; --j) {
        softPwmWrite (ledMap [i], j) ;
        delay (10) ;
      }
    }
  }

}
