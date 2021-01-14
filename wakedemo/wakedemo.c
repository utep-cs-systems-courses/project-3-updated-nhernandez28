#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "stateMachine.h"
#include "buzzer.h"
#include "switches.h"

//#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int fontFgColor = COLOR_GREEN;
long color;
static int prev_s= 0;

u_char c_width = (screenWidth/2) + 1;
u_char c_height = (screenHeight/2) + 1;

//draws diamond shape
void drawDiamond(u_char col, u_char row, u_char center, u_int color)
{
  u_char r;
  u_char c;

  for(c = 0; c < center; c++){
    for(r = center; r < center * 2 - c; r++){
      drawPixel(center + col + c, row + r, color);
      drawPixel(center + col - c, row + r, color);
    }
  }

  for(r = 0; r < center; r++){
    for(c = 0; c < r; c++){
      drawPixel(center + col + c, row + r, color);
      drawPixel(center + col - c, row + r, color);
    }
  }
}

void wdt_c_handler()
{
  //each count is for a specific action(s)
  static int secCount = 0;
  static int secCount2 = 0;
  static int secCount3 = 0;

  //if the first switch is pressed
  if (switch_state_down == 1) {		/* once/sec */
    //will play sound
    if(++secCount %5 == 0){
      buzzer_advance();
    }
    //goes to the next state
    if(secCount == 250){
       state_advance();
       secCount = 0;
    }
  }
  //for switches 2 and 3. will make no sounds
  if(++secCount2 == 250){
    //goes to next state
    state_advance();
    secCount2 = 0;
    secCount2++;
    redrawScreen = 1;
  }
  //if fourth switch is pressed
  if(switch_state_down == 4){
    //makes 4th switch play a noise
    buzzer_advance();
    if(++secCount3 == 250){
      secCount3 == 0;
      //color of the text
      fontFgColor = (fontFgColor == COLOR_GREEN ? COLOR_PINK : COLOR_GREEN);
      redrawScreen = 1;
    }
  }
}

void main()
{
  led_init();
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  
  configureClocks();
  lcd_init();
  buzzer_init();
  switch_init();
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  clearScreen(COLOR_WHITE);
  
  while (1) {			/* forever */
    if(redrawScreen){
      switch(switch_state_down){
      case 0:
	//will always show the TEXT
	drawString11x16(20, 10, "Welcome!", COLOR_PINK, COLOR_WHITE);
	drawString5x7(15, 30, "Press any button", COLOR_PINK, COLOR_WHITE);
	break;
      case 1:
	//if prev switch was the 2nd then in will clear the shapes
	if(prev_s == 2){
	  clearShapes(25, 30, 20);
	}else if(prev_s == 3){                        //if prev switch was the 3rd it will clear its shapes
	  clearShapes(50, 50, 10);
	}

	//if first switch is pressed before any other the it will draw this diamond
	//draws one pink diamond
	drawShapes(COLOR_PINK, 100, 100, 10);
	prev_s = 1;
	break;
      case 2:
	if(prev_s == 1){
	  clearShapes(100, 100, 10);
	}else if(prev_s == 3){
	  clearShapes(50, 50, 10);
	}
	//draws two larger yellow diamonds
	drawShapes(COLOR_YELLOW, 25, 30, 20);
	prev_s = 2;
	break;
      case 3:
	if(prev_s == 1){
	  clearShapes(100, 100, 10);
	}else if(prev_s == 2){
	  clearShapes(25, 30, 20);
	}
	//draws to small deperated blue diamonds
	drawShapes(COLOR_BLUE, 50, 50, 10);
	prev_s = 3;
	break;
	//will clear shapes from 1-3 if they were pressed before the 4th switch
	//4th switch doesnt draw anything
      case 4:
	if(prev_s == 1){
	  clearShapes(100, 100, 10);
	}else if(prev_s == 2){
	  clearShapes(25, 30, 20);
	}else if(prev_s == 3){
	  clearShapes(50, 50, 10);
	}
      }
    }
    
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}
