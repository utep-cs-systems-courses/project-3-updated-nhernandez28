#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "stateMachine.h"
#include "buzzer.h"
#include "switches.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int color = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount++;
  if (++secCount == 250) {		/* once/sec */
    secCount = 0;
    color = (color == COLOR_GREEN) ? COLOR_PINK : COLOR_GREEN;
    redrawScreen = 1;
  }
  else if(secCount == 250 && switch_state_down == 0){
    redrawScreen = 1;
    secCount = 0;
  }
  else if(secCount == 250 && switch_state_down == 1){
    secCount = 0;
    redrawScreen = 1;
  }
  if(secCount != 250 && switch_state_down == 2){
    secCount = 0;
    redrawScreen = 1;
  }
  if(secCount != 250 && switch_state_down == 3){
    secCount = 0;
    redrawScreen = 1;
  }
}
  
void main()
{
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  buzzer_init();
  switch_init(15);
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  //static char state = 0;
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      //drawString5x7(20,20, "hello", fontFgColor, COLOR_BLUE);
      drawString11x16(20, 10, "Welcome!", color, COLOR_BLACK);
      drawString5x7(15, 30, "Press any button", color, COLOR_BLACK);

      switch(switch_state_down){
      case 1:
	//fillRectangle(30, 30, 60, 60, color);
	drawDiamond(40, 100, 10, color);
	//redrawScreen = 0;
	//drawState();
	//state = 1;
	break;
      case 2:
	buzzer_set_period(3000);
	//drawState();
	//state = 2;
	break;
      case 3:
	//clearScreen(COLOR_BLACK);
	drawDiamond(55, 40, 10, COLOR_WHITE);
	drawDiamond(55, 60, 10, COLOR_ORANGE);
	drawDiamond(55, 80, 10, COLOR_BLUE);
	drawDiamond(30, 70, 10, COLOR_RED);
	
	//drawState();
	//state = 3;
	break;
      case 4:
	//drawDiamond(50, 50, 10, color);
	drawDiamond(75, 70, 10, color);
	fillRectangle(85, 80, 10, 10, color);
	drawDiamond(100, 90, 10, COLOR_ORANGE);
	fillRectangle(110, 100, 10, 10, COLOR_ORANGE);
	drawDiamond(50, 50, 10, COLOR_ORANGE);
	fillRectangle(60, 60, 10, 10, COLOR_ORANGE);
	//drawState();
	//state = 0;
	break;
	/*default:
	state = 0;
	break;*/
      }
      redrawScreen = 0;
      //clearScreen(COLOR_BLACK);
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}
