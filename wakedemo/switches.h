#ifndef switches_included
#define switches_included

#define SW1 BIT0 //switch 1
#define SW2 BIT1 //switch 2
#define SW3 BIT2 //switch 3
#define SW4 BIT3 //switch 4
#define SWITCHES (SW1 | SW2 | SW3 | SW4) //switches

void switch_red();
void switch_init();
void switch_interrupt_handler();

extern char switch_state_down, s_1, s_2, s_3, s_4;

#endif //included
