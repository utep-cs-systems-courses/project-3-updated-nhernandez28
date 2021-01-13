#include <msp430.h>
#include "led.h"

unsigned char red_on = 0, green_on = 0;
unsigned char changed_led = 0;

static char redVal[] = {0, LED_GREEN};
static char greenVal[] = {0, LED_GREEN};

void led_init()
{
  P1DIR |= LEDS;
  changed_led = 1;
  led_update();
}

void led_update()
{
  if(changed_led){
    char ledFlags = redVal[red_on] | greenVal[green_on];

    P1OUT &= (0xff^LEDS) | ledFlags;
    P1OUT |= ledFlags;
    changed_led = 0;
  }
}
