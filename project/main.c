#include <msp430.h>
#include <libTimer.h>
#include "lcddraw.h"
#include "stateMachine.h"
#include "buzzer.h"
#include "led.h"
#inlcude "lcddraw.h"
#include "lcdutils.h"
#include "p2switches.h"

short changed = 1;

void main()
{
  P1DIR |= LED_GREEN;
  P1OUT |= LED_GREEN;
  configureClocks();
  led_init();
  buzzer_init();

  enableWDTInterrupts();
  or_sr(0x8);

  clearScreen(COLOR_WHITE);
  while(1){
    if(changed){
      changed = 0;
    }
    P1OUT &= ~LED_GREEN;
    or_sr(0x10);
    P1OUT |= LED_GREEN;
  }
}
