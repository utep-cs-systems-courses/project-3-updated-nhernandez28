#include <msp430.h>
#include "lcdutils.h"
#include "lcddraw.h"

void drawDiamond(u_char col, u_char row, u_char center, u_int colorBGR)
{
  u_char r;
  u_char c;
  // u_char center = 10;

  /*for(r = center; r > 0; r--){
    for(c = center; c >= r; c--){
      drawPixel(col + c, row + r, colorBGR);
      drawPixel(col + c, row - r + 1, colorBGR);
    }
    }*/
  for(c = 0; c < center; c++){
    for(r = center; r < center * 2 - c; r++){
      drawPixel(center + col + c, row + r, colorBGR);
      drawPixel(center + col - c, row + r, colorBGR);
    }
  }

  for(r = 0; r < center; r++){
    for(c = 0; c < r; c++){
      drawPixel(center + col + c, row + r, colorBGR);
      drawPixel(center + col - c, row + r, colorBGR);
    }
  }
  
  /*
  switch(state){
  case 0:
    drawDiamond(30, 30, COLOR_WHITE);
    state = 1;
    break;
  case 1:
    drawDiamond(30, 30, COLOR_WHITE);
    drawDiamond(30, 30, COLOR_WHITE);
    state = 2;
    break;
  case 2:
    drawDiamond(30, 30, COLOR_WHITE);
    drawDiamond(30, 30, COLOR_WHITE);
    drawDiamond(30, 30, COLOR_WHITE);
    state = 3;
    break;
  case 3:
    drawDiamond(30, 30, COLOR_WHITE);
    drawDiamond(30, 30, COLOR_WHITE);
    drawDiamond(30, 30, COLOR_WHITE);
    state = 4;
    break;
  default:
    state = 0;
    break;
  }
  */
}
