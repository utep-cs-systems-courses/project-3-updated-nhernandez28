#include <msp430.h>
#include "stateMachine.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

static char state_dim = 0;
static char select_dim = 0;
static char count = 0;

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
