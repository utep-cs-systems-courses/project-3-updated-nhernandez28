#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

//notes
/*#define A3 2273
#define B3 2025
#define C3 3846
#define D4 1703
#define E3 3033
#define F4 1432
#define G4 1276
*/

void buzzer_init()
{
  timerAUpmode(); // used to drive speaker
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6; // enable output to speaker (P2.6)
}

void buzzer_set_period(short cycles)
{
  // buzzer clock = 2MHz. (period of 1k results in 2kHz tone)
  CCR0 = cycles;
  CCR1 = cycles >> 1; // one half cycle
}

/*void tune1()
{

  int i = 0;

  int notes[] = {A3, B3, C3, D4};

  while(i < sizeof(notes)){
    int t1 = 0;

    while (t1 < 15){
      int t2 = 0;

      while(t2 < 20000){
	t2++;
      }
      t1++;
    }
*/
