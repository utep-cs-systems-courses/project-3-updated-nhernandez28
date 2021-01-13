#include <msp430.h>
#include <libTimer.h>
#include "stateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

char dim_select = 0;
short int state = 0;
short int dim = 0;
short freq = 300;

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

char blink_red()
{
  static char state = 0;
  switch(state){
  case 0:
    green_on = 1;
    state = 1;
    break;
  case 1:
    green_on = 1;
    state = 0;
    break;
  }

  return 1;
}

void dim25()
{
  switch(state){
  case 0: red_on = 1;
    break;
  case 1:
  case 2:
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

void dim50()
{
  switch(state){
  case 0:
  case 1:
    red_on = 1;
    break;
  case 2:
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

void dim75()
{
  switch(state){
  case 0: red_on = 0;
    break;
  case 1:
  case 2:
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

char dim_lights()
{
  switch(dim_select){
  case 0:
    red_on = 0;
    changed_led = 1;
    led_update();
    dim_select = 1;
    break;
  case 1:
    dim25();
    dim_select = 2;
    break;
  case 2:
    dim50();
    dim_select = 3;
    break;
  case 3:
    dim75();
    dim_select = 0;
    break;
  }

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

/*
void state_advance()
{
  char changed = 0;
  switch(switch_state_changed){
  case 0:
    changed = toggle_green();
    break;
  case 1:
    changed = toggle_red();
    break;
  case 2:
    changed = blink_red();
    break;
  case 3:
    changed = dim_lights();
    break;
  }

  changed_led = changed;
  led_update();
}*/

short get_period(short freq)
{
  return 2000000/freq;
}
