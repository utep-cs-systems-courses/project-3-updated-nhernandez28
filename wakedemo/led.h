#ifndef led_included
#define led_included
#include <msp430.h>

#define LED_RED BIT0                 // p1.0
#define LED_GREEN BIT6               //p1.6
#define LEDS (BIT0 | BIT6)

void led_init();
void led_update();

//boolean flags
extern unsigned char red_on, green_on, changed_led;

#endif
