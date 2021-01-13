#include <msp430.h>
#include <libTimer.h>
#include "stateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

char button_state = 0;
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

char state1()
{
  static short curr = 0;
  
  switch(curr){
  case 0:
    red_on = 1;
    state = 1;
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

char state2()
{
  static char state = 0;
  switch(state){
  case 0:
    green_on = 1;
    state = 1;
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
    break;
  case G:
    changed = toggle_green();
    color = R;
    buzzer_set_period(1000);
    break;
  }

  changed_led = changed;
  led_update();
}

char state4()
{
  red_on = 0;
  changed_led = 1;
  led_update();
  dim75();
  return 1;
}

void dim_advance()
{
  switch(dim){
  case 0:
    red_on = 1;
    changed_led = 1;
    led_update();
    break;
  case 1:
    dim25();
    break;
  case 2:
    dim50();
    break;
  case 3:
    dim75;
    break;
  default:
    break;
  }
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
  case 1:
    changed = toggle_green();
    break;
  case 2:
    changed = state2();
    break;
  case 3:
    changed = state3();
    break;
  case 4:
    changed = state4();
    break;
  }

  changed_led = changed;
  led_update();
}*/

short get_period(short freq)
{
  return 2000000/freq;
}

/*void diamondShape()
{
  switch(state){
  case 0:
    clearScreen(COLOR_BLACK);
    drawDiamond(40, 100, 10, COLOR_PINK);
    state = 1;
    break;
  case 1:
    clearScreen(COLOR_BLACK);
    drawDiamond(50, 100, 10, COLOR_PINK);
    state = 2;
    break;
  case 2:
    clearScreen(COLOR_BLACK);
    drawDiamond(60, 100, 10, COLOR_PINK);
    state = 3;
    break;
  case 3:
    clearScreen(COLOR_BLACK);
    drawDiamond(70, 100, 10, COLOR_PINK);
    state = 4;
    break;
  case 4:
    clearScreen(COLOR_BLACK);
    drawDiamond(80, 100, 10, COLOR_PINK);
    state = 1;
    break;
  }
}

void changeColors()
{
  switch(state){
  case 1:
    clearScreen(COLOR_BLACK);
    drawDiamond(55, 80, 10, COLOR_GREEN);
    state = 2;
    break;
  case 2:
    clearScreen(COLOR_BLACK);
    drawDiamond(55, 80, 10, COLOR_PINK);
    state = 3;
    break;
  case 3:
    clearScreen(COLOR_BLACK);
    drawDiamond(55, 80, 10, COLOR_GREEN);
    state = 4;
    break;
  case 4:
    clearScreen(COLOR_BLACK);
    drawDiamond(55, 80, 10, COLOR_PINK);
    state = 1;
    break;
  }
}
*/
