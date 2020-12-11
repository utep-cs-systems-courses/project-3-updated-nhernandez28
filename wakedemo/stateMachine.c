#include <msp430.h>
#include "stateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

static int state = 1;
static char tune = 0;

void diamondShape()
{
  drawDiamond(COLOR_WHITE);
  drawString11x16(40, 60, "Wlcome!", COLOR_WHITE, COLOR_BLUE);
  switch(tune){
  case 0:
    buzzer_set_period(3136);
    tune++;
    break;
  case 1:
    buzzer_set_period(2093);
    tune++;
    break;
  case 2:
    buzzer_set_period(2093);
    tune++;
    break;
  case 3:
    buzzer_set_period(2334);
    note = 0;
    break;
  }
}

// 1/4
void dimAt25()
{
  switch(state){
  case 0:
    red_on = 0;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 2;
    break;
  case 2:
    red_on = 0;
    state = 3;
    break;
  case 3:
    red_on = 1;
    state = 0;
    break;
  }

  changed_led = 1;
  led_update();
}

// 1/2
char toggle_red()
{
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

  changed_led = 1;
  led_update();
  return changed_led;
}

// 3/4
void dimAt75()
{
  switch(state){
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 1;
    state = 2;
    break;
  case 2:
    red_on = 1;
    state = 3;
    break;
  case 3:
    red_on = 0;
    state = 0;
  }
  
  changed_led = 1;
  led_update();
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

/*
void tunes()
{
  switch(state){
  case 1:
    tune = 2000;
    state++;
    break;
  case 2:
    tune = 3000;
    state++;
    break;
  case 3:
    tune = 4000;
    state = 0;
    break;
  default:
    tune = 0;
    break;
  }

  buzzer_set_period(3000000 / tune);
}
*/

static int a = 1;
static int tune1 = 0;

void b_s_p(int n)
{
  buzzer_set_period(n);
}
void buzzer_advance()
{
  static char tune = 0;
  switch(tune){
  case 0:
    buzzer_set_period(3000000 / 2000);
    tune++;
    break;
  case 1:
    buzzer_set_period(3000000 / 3000);
    tune++;
    break;
  case 2:
    buzzer_set_period(300000 / 4000);
    tune++;
    break;
  case 3:
    buzzer_set_period(3000000 / 5000);
    tune = 0;
    break;
  default:
    tune++;
  }
}

void state_advance()
{
  char changed = 0;
  static enum {R = 0, G = 1} color = G;
  switch(color){
  case R:
    changed = toggle_red();
    color = G;
    buzzer_advance();
    break;
  case G:
    changed = toggle_green();
    color = R;
    buzzer_advance();
    break;
  }

  changed_led = changed;
  led_update();
}
/*static char state_dim = 0;
static char select_dim = 0;
static char tune = 0;

// 1/4
void dimAt25()
{
  if(count < 3){
    count++;
    switch(select_dim){
    case 0:
      r_on = 0;
      select_dim = 1;
      break;
    case 1:
      r_on = 0;
      select_dim = 2;
      break;
    case 2:
      r_on = 1;
      select_dim = 0;
      break;
    }
    led_update();
  }else{
    count = 0;
    state_dim = 0;
  }
}

// 1/2
void dimAt50()
{
  if(count < 2){
    count++;
    select_dim = red_state_machine(select_dim);
    led_update();
  }else{
    count = 0;
    state_dim = 1;
  }
}

// 3/4
void dimAt75()
{
  if(count < 3){
    count++
    switch(select_dim){
    case 0:
      r_on = 1;
      select_dim = 1;
      break;
    case 1:
      r_on = 1;
      select_dim = 2;
      break;
    case 2:
      r_o = 0;
      select_dim = 0;
      break;
    }
    led_update();
  }else{
    count = 0;
    state_dim = 2;
  }
}


//will turn green led on
void gLedOn()
{
  g_on = 1;
  r_on = 0;
  led_update();
}

//will turn red led off
void rLedOff()
{
  r_on = 0;
  led_update();
}

//will turn red led on
void rLedOn()
{
  r_on = 1;
  g_on = 0;
  led_update();
}

// will play increasing notes
void tune()
{
  static char note = 0;
  //change this to <= 0
  if((note % 2) == 0){
    drawDiamond(50,50, COLOR_PINK, 50);
  }else{
    drawDiamond(50,50, COLOR_WHITE, 50);
  }

  switch(note){
  case 0:
    buzzer_set_period(A);
    note++
      break;
  case 1:
    buzzer_set_period(A);
    note++
      break;
  case 2:
    buzzer_set_period(A);
    note++
      break;
  case 3:
    buzzer_set_period(A);
    note++
      break;
  case 4:
    buzzer_set_period(B);
    note++
      break;
  case 5:
    buzzer_set_period(C);
    note++
      break;
  case 6:
    buzzer_set_period(D);
    note++
      break;
  case 7:
    buzzer_set_period(E);
    note++
      break;
  case 8:
    buzzer_set_period(F);
    note++
      break;
  case 9:
    buzzer_set_period(G);
    note++
      break;
  }
}
*/
