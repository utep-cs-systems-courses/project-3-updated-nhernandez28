#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachine.h"
#include "buzzer.h"
#include "libTimer.h"

static unsigned char last_switch, current_switch;

char switch_state_down = 0;
char s_1, s_2, s_3, s_4;

static char switch_update_interrupt_sense()
{
  char p2val = P2IN;
  
  //update switch interrupt to detect changes from current buttons
  P2IES |= (p2val & SWITCHES); //switch up then sense down
  P2IES &= (p2val | ~SWITCHES); //switch down then sense up
  return p2val;
}

void switch_init()
{
  //set up switch
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;

  switch_update_interrupt_sense();
  //led_update();
}

unsigned int switch_read()
{
  unsigned int switch_changed = current_switch ^ last_switch;
  last_switch = current_switch;
  return current_switch | (switch_changed << 8);
}

void __interrupt_vec(PORT2_VECTOR) Port_2()
{
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  s_1 = (p2val & SW1) ? 0 : 1;
  s_2 = (p2val & SW2) ? 0 : 1;
  s_3 = (p2val & SW3) ? 0 : 1;
  s_4 = (p2val & SW4) ? 0 : 1;

  if(s_1){
    switch_state_down = 1;
  }else if(s_2){
    switch_state_down = 2;
  }else if(s_3){
    switch_state_down = 3;
  }else if(s_4){
    switch_state_down = 4;
  }
}
