#include "wiring-pitaya.h"
#include "soft-pwm.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define RANGE		100
#define	NUM_LEDS	  1

int ledMap [NUM_LEDS] = { 0 } ;

int values [NUM_LEDS] = { 25 } ;

int main ()
{
  int i, j ;
  char buf [80] ;

  wiringPitayaSetup ()  ;

  for (i = 0 ; i < NUM_LEDS ; ++i)
  {
    softPwmCreate (ledMap [i], 0, RANGE) ;
    printf ("%3d, %3d, %3d\n", i, ledMap [i], values [i]) ;
  }

  fgets (buf, 80, stdin) ;

// Bring all up one by one:

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

  fgets (buf, 80, stdin) ;

// All Down

  /* for (i = 100 ; i > 0 ; --i) */
  /* { */
  /*   for (j = 0 ; j < NUM_LEDS ; ++j) */
  /*     softPwmWrite (ledMap [j], i) ; */
  /*   delay (10) ; */
  /* } */

  /* fgets (buf, 80, stdin) ; */

  /* for (;;) */
  /* { */
  /*   for (i = 0 ; i < NUM_LEDS ; ++i) */
  /*     softPwmWrite (ledMap [i], values [i]) ; */

  /*   delay (50) ; */

  /*   i = values [0] ; */
  /*   for (j = 0 ; j < NUM_LEDS - 1 ; ++j) */
  /*     values [j] = values [j + 1] ; */
  /*   values [NUM_LEDS - 1] = i ; */
  /* } */
}

