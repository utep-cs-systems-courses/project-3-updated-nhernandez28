#include <msp430.h>
#include <libTimer.h>
#include "stateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

char buttonState = 0;
short int state = 0;
short freq = 500;

//will draw diamonds
void drawShapes(int COLOR, int width, int height, int center)
{
  u_char c_width = screenWidth/2 + 1;
  u_char c_height = screenHeight/2 + 1;

  drawDiamond(c_width - width, c_height - height, center, COLOR);
  drawDiamond(c_width, c_height, center, COLOR);
}

//will clear prev shapes drawn
void clearShapes(int width, int height, int center)
{
  u_char c_width = screenWidth/2 + 1;
  u_char c_height = screenHeight/2 +1;

  drawDiamond(c_width - width, c_height - height, center, COLOR_BLACK);
  drawDiamond(c_width, c_height, center, COLOR_BLACK);
}


char toggle_red()
{
  static char state = 0;
  switch(state){
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }

  return 1;
}

char toggle_green()
{
  char changed = 0;

  if(red_on){
    green_on ^= 1;
    changed = 1;
  }

  return changed;
}

//red flashes and plays sound
char state1()
{
  static short curr = 0;
  switch(curr){
  case 0:
    red_on = 1;
    state = 0;
    curr = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    curr = 0;
    break;
  }

  return 1;
}

//red flashes
char state2()
{
  static char state = 0;
  switch(state){
  case 0:
    green_on = 1;
    buzzer_set_period(1000);
    break;
  case 1:
    green_on = 0;
    state = 0;
    buzzer_set_period(0);
    break;
  }

  return 1;
}

char state3()
{
  char changed = 0;
  static enum {R=0, G=1} color = G;
  switch(color){
  case R:
    changed = toggle_red();
    color = G;
    buzzer_set_period(2000);
  case G:
    changed = toggle_green();
    color = R;
    buzzer_set_period(1000);
  }

  changed_led = changed;
  led_update();
}

char state4()
{
  red_on = 0;
  buzzer_set_period(0);
  changed_led = 1;
  led_update();
  return 1;
}

void buzzer_advance()
{
  static char count = 0;
  switch(count){
  case 0:
    buzzer_set_period(1000);
    count = 1;
    break;
  case 1:
    buzzer_set_period(5000);
    count = 2;
    break;
  case 2:
    buzzer_set_period(3000);
    count = 3;
    break;
  case 3:
    buzzer_set_period(7000);
    count = 4;
    break;
  default:
    count = 0;
  }
}

void dim25()
{
  switch(state){
  case 0:
    red_on = 0;
    break;
  case 1:
    red_on = 0;
    break;
  case 2:
    red_on = 0;
    break;
  case 3:
    red_on = 1;
    break;
  default: state = 0;
    break;
  }

  changed_led = 1;
  led_update();
}

void dim50()
{
  switch(state){
  case 0:
    red_on = 0;
    break;
  case 1:
    red_on = 1;
    break;
  case 2:
    red_on = 0;
    break;
  case 3:
    red_on = 1;
    break;
  default:
    state = 0;
    break;
  }

  changed_led = 1;
  led_update();
}

void dim75()
{
  switch(state){
  case 0:
    red_on = 1;
    break;
  case 1:
    red_on = 1;
    break;
  case 2:
    red_on = 1;
    break;
  case 3:
    red_on = 0;
    break;
  default:
    state = 0;
    break;
  }

  changed_led = 1;
  led_update();
}

short get_period(short freq)
{
  return 2000000/freq;
}
