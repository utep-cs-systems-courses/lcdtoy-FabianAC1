/** \file lcddraw.c
 *  \brief Adapted from RobG's EduKit
 */
#include "lcdutils.h"
#include "lcddraw.h"
/** Draw single pixel at x,row 
 *
 *  \param col Column to draw to
 *  \param row Row to draw to
 *  \param colorBGR Color of pixel in BGR
 */
void drawPixel(u_char col, u_char row, u_int colorBGR) 
{
  lcd_setArea(col, row, col, row);
  lcd_writeColor(colorBGR);
}

void drawrainbow(){  // draws a rainbow and displays a message
  u_int arrColor[] = {COLOR_YELLOW,COLOR_BLUE,COLOR_RED,COLOR_ORANGE,COLOR_GREEN};
  u_char i,j;
  int n =0;
  for(j=0;j<128;j++){
    for(i=0; i<160;i++){
      drawPixel(j,i,arrColor[n]);
    }
    if(j%10 ==0){
    n++;
    }
    if(n == 4){
      n==0;
    }
  }
  drawString5x7(60,80,"PROJECT 3", COLOR_BLACK,COLOR_YELLOW);
  drawString5x7(60,90,"THE END", COLOR_BLACK,COLOR_YELLOW);
  drawString5x7(60,100,"........", COLOR_BLACK,COLOR_YELLOW);
}

void drawMe(u_int color){ //this method draws a star and a square resembeling patrick and spongebob
   u_char i, j;
    for(j=0;j<12;j++){
      for(i=0; i<8;i++){
	drawPixel(j+40,i+70,COLOR_RED);
      }
    }

    for(j=0; j<18;j++){
      for(i=0;i<18;i++){
	drawPixel(j+60,i+95,color);
      }
    }
    for(j=0;j<6;j++){
      u_char a = 6-j;
      u_char b = j;
      u_char c = 6-j;
      for(i=j;i<6;i++){
	drawPixel(a+40,i+64,COLOR_RED);
       	drawPixel(b+46,i+64,COLOR_RED);
       	drawPixel(52-j,c+77,COLOR_GREEN);
       	drawPixel(b+40,83-i,COLOR_GREEN);
	c--;
      }
    }
    for(j=0;j<8;j++){
      u_char a = 8-j;
      for(i=j; i<8; i++){
	drawPixel(j+52,a+69,COLOR_RED);
	drawPixel(40-j,a+69,COLOR_RED);
	a--;
      }
    }
  }
 
void drawBigJelly(u_char col, u_char row,u_int color){ // this method draws a large jellyfish 
  u_char j,i;
   for(j=0; j<10;j++){
      for(i=0;i<10;i++){
	drawPixel(j+col,i+row,color);
      }
      
    }

   for(j=8;j<16;j++){

     drawPixel(col,j+row,color);
     drawPixel(col+9,j+row,color);
     drawPixel(col+3,j+row,color);
     drawPixel(col+7,j+row,color);
      
   }

   

}

void drawJelly(u_char col, u_char row,u_int color){ // this method draws a jellyfish 
  u_char j,i;
   for(j=0; j<8;j++){
      for(i=0;i<8;i++){
	drawPixel(j+col,i+row,color);
      }
      
    }

   for(j=8;j<16;j++){

     drawPixel(col,j+row,color);
     drawPixel(col+7,j+row,color);
     drawPixel(col+4,j+row,color);
   }

   

}
/** Fill rectangle
 *
 *  \param colMin Column start
 *  \param rowMin Row start
 *  \param width Width of rectangle
 *  \param height height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void fillRectangle(u_char colMin, u_char rowMin, u_char width, u_char height, 
		   u_int colorBGR)
{
  u_char colLimit = colMin + width, rowLimit = rowMin + height;
  lcd_setArea(colMin, rowMin, colLimit - 1, rowLimit - 1);
  u_int total = width * height;
  u_int c = 0;
  while ((c++) < total) {
    lcd_writeColor(colorBGR);
  }
}

/** Clear screen (fill with color)
 *  
 *  \param colorBGR The color to fill screen
 */
void clearScreen(u_int colorBGR) 
{
  u_char w = screenWidth;
  u_char h = screenHeight;
  fillRectangle(0, 0, screenWidth, screenHeight, colorBGR);
}

/** 5x7 font - this function draws background pixels
 *  Adapted from RobG's EduKit
 */
void drawChar5x7(u_char rcol, u_char rrow, char c, 
     u_int fgColorBGR, u_int bgColorBGR) 
{
  u_char col = 0;
  u_char row = 0;
  u_char bit = 0x01;
  u_char oc = c - 0x20;

  lcd_setArea(rcol, rrow, rcol + 4, rrow + 7); /* relative to requested col/row */
  while (row < 8) {
    while (col < 5) {
      u_int colorBGR = (font_5x7[oc][col] & bit) ? fgColorBGR : bgColorBGR;
      lcd_writeColor(colorBGR);
      col++;
    }
    col = 0;
    bit <<= 1;
    row++;
  }
}

/** Draw string at col,row
 *  Type:
 *  FONT_SM - small (5x8,) FONT_MD - medium (8x12,) FONT_LG - large (11x16)
 *  FONT_SM_BKG, FONT_MD_BKG, FONT_LG_BKG - as above, but with background color
 *  Adapted from RobG's EduKit
 *
 *  \param col Column to start drawing string
 *  \param row Row to start drawing string
 *  \param string The string
 *  \param fgColorBGR Foreground color in BGR
 *  \param bgColorBGR Background color in BGR
 */
void drawString5x7(u_char col, u_char row, char *string,
		u_int fgColorBGR, u_int bgColorBGR)
{
  u_char cols = col;
  while (*string) {
    drawChar5x7(cols, row, *string++, fgColorBGR, bgColorBGR);
    cols += 6;
  }
}


/** Draw rectangle outline
 *  
 *  \param colMin Column start
 *  \param rowMin Row start 
 *  \param width Width of rectangle
 *  \param height Height of rectangle
 *  \param colorBGR Color of rectangle in BGR
 */
void drawRectOutline(u_char colMin, u_char rowMin, u_char width, u_char height,
		     u_int colorBGR)
{
  /**< top & bot */
  fillRectangle(colMin, rowMin, width, 1, colorBGR);
  fillRectangle(colMin, rowMin + height, width, 1, colorBGR);

  /**< left & right */
  fillRectangle(colMin, rowMin, 1, height, colorBGR);
  fillRectangle(colMin + width, rowMin, 1, height, colorBGR);
}

