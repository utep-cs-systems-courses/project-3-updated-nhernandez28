/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(10, 10, "Font 5x7", COLOR_PINK, COLOR_BLUE);

  drawString11x16(30, 20, "Font 11x16", COLOR_PINK, COLOR_BLUE);

  drawDiamond(50, 40, 30, COLOR_PINK);
  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  
}
