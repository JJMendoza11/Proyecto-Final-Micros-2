/*
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    OLED_Screen_Driver.c
 * @brief   Application entry point.
 */

/* TODO: insert other include files here. */
#include <stdio.h>
#include <stdlib.h>
#include "I2CDrive.h"
#include "OLED_Screen_Driver.h"
/* TODO: insert other definitions and declarations here. */

#define SSD1306_MEMORYMODE          0x20 ///< See datasheet
#define SSD1306_COLUMNADDR          0x21 ///< See datasheet
#define SSD1306_PAGEADDR            0x22 ///< See datasheet
#define SSD1306_SETCONTRAST         0x81 ///< See datasheet
#define SSD1306_CHARGEPUMP          0x8D ///< See datasheet
#define SSD1306_SEGREMAP            0xA0 ///< See datasheet
#define SSD1306_DISPLAYALLON_RESUME 0xA4 ///< See datasheet
#define SSD1306_DISPLAYALLON        0xA5 ///< Not currently used
#define SSD1306_NORMALDISPLAY       0xA6 ///< See datasheet
#define SSD1306_INVERTDISPLAY       0xA7 ///< See datasheet
#define SSD1306_SETMULTIPLEX        0xA8 ///< See datasheet
#define SSD1306_DISPLAYOFF          0xAE ///< See datasheet
#define SSD1306_DISPLAYON           0xAF ///< See datasheet
#define SSD1306_COMSCANINC          0xC0 ///< Not currently used
#define SSD1306_COMSCANDEC          0xC8 ///< See datasheet
#define SSD1306_SETDISPLAYOFFSET    0xD3 ///< See datasheet
#define SSD1306_SETDISPLAYCLOCKDIV  0xD5 ///< See datasheet
#define SSD1306_SETPRECHARGE        0xD9 ///< See datasheet
#define SSD1306_SETCOMPINS          0xDA ///< See datasheet
#define SSD1306_SETVCOMDETECT       0xDB ///< See datasheet

#define SSD1306_SETSTARTLINE        0x40 ///< See datasheet

#define SSD1306_EXTERNALVCC         0x01 ///< External display voltage source
#define SSD1306_SWITCHCAPVCC        0x02 ///< Gen. display voltage from 3.3V

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL                      0x2F
#define SSD1306_DEACTIVATE_SCROLL                    0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA             0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL              0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL               0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  0x2A

#define Message_Leght		3


#define ssd1306_swap(a, b) { uint16_t t = a; a = b; b = t;}

/*
 * @brief   Application entry point.
 */




static uint8_t au8OLED_Leght[enCompleteMessage] = {SSD1306_I2C_ADDRESS, 0x00, 0x00};				/*Co = 0x00 and Data 2.	 */
uint8_t  x_pos = 0;
uint8_t  y_pos = 0;
uint8_t text_size = 0;

#define Message_Leght		3

uint8_t SSD1306_Begin(void){
	au8OLED_Leght[enControlByte] = 0x00;

	au8OLED_Leght[enCommandByte] = SSD1306_DISPLAYOFF;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_SETDISPLAYCLOCKDIV;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);
	au8OLED_Leght[enCommandByte] = 0x80;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_SETMULTIPLEX;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_LCDHEIGHT - 1;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_SETDISPLAYOFFSET;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = 0x00;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_SETSTARTLINE;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_CHARGEPUMP;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = 0x14;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_MEMORYMODE;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = 0x00;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_SEGREMAP | 0x1;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_COMSCANDEC;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_SETCOMPINS;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);
	au8OLED_Leght[enCommandByte] = 0x02;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_SETCONTRAST;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);
	au8OLED_Leght[enCommandByte] = 0x8F;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);


	au8OLED_Leght[enCommandByte] = SSD1306_SETPRECHARGE;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);
	au8OLED_Leght[enCommandByte] = 0xF1;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_SETVCOMDETECT;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);
	au8OLED_Leght[enCommandByte] = 0x40;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_DISPLAYALLON_RESUME;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_NORMALDISPLAY;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_DISPLAYON;
	 I2C_vfnSendData (&au8OLED_Leght[enAddressByte], Message_Leght);

	return 1;
}

void SSD1306_Display(void)
{

	au8OLED_Leght[enControlByte] = 0x00;

	au8OLED_Leght[enCommandByte] = SSD1306_PAGEADDR;
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);
	au8OLED_Leght[enCommandByte] = 0x00;								// Page start address (0 = reset)
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);
	au8OLED_Leght[enCommandByte] = 0x03;									// Page end address
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_COLUMNADDR;
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);
	au8OLED_Leght[enCommandByte] = 0x00;								// Column start address (0 = reset)
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);
	au8OLED_Leght[enCommandByte] = SSD1306_LCDWIDTH  - 1;				// Column end address (127 = reset)
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);

	for (uint16_t i = 0; i <(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT / 8); i++){
    // send a bunch of data in one mission
	au8OLED_Leght[enControlByte] = SSD1306_SETSTARTLINE;
	au8OLED_Leght[enCommandByte] = ssd1306_buffer[i];
     I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);
	}

}

void SSD1306_ClearDisplay(void)
{
	for (uint16_t i = 0; i <(SSD1306_LCDWIDTH*SSD1306_LCDHEIGHT / 8); i++){
		ssd1306_buffer[i] = 0;
	}
}


void SSD1306_DrawPixel(uint8_t x, uint8_t y, _Bool color)
{
	  if (color)
	    ssd1306_buffer[x + (uint16_t)(y / 8) * SSD1306_LCDWIDTH] |=  (1 << (y & 7));
	  else
	    ssd1306_buffer[x + (uint16_t)(y / 8) * SSD1306_LCDWIDTH] &=  ~(1 << (y & 7));
}

void SSD1306_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, _Bool color)
{
	  _Bool steep;
	  char ystep;
	  uint8_t dx, dy;
	  int16_t err;
	  steep = abs(y1 - y0) > abs(x1 - x0);
	  if (steep) {
	    ssd1306_swap(x0, y0);
	    ssd1306_swap(x1, y1);
	  }
	  if (x0 > x1) {
	    ssd1306_swap(x0, x1);
	    ssd1306_swap(y0, y1);
	  }
	  dx = x1 - x0;
	  dy = abs(y1 - y0);

	  err = dx / 2;
	  if (y0 < y1)
	    ystep = 1;
	  else
	    ystep = -1;

	  for (; x0 <= x1; x0++) {
	    if (steep) {
	      if(color) SSD1306_DrawPixel(y0, x0, 1);
	      else      SSD1306_DrawPixel(y0, x0, 0);
	    }
	    else {
	      if(color) SSD1306_DrawPixel(x0, y0, 1);
	      else      SSD1306_DrawPixel(x0, y0, 0);
	    }
	    err -= dy;
	    if (err < 0) {
	      y0  += ystep;
	      err += dx;
	    }
	  }
}

void SSD1306_DrawFastHLine(uint8_t x, uint8_t y, uint8_t w, _Bool color)
{
   SSD1306_DrawLine(x, y, x + w - 1, y, color);
}

void SSD1306_DrawFastVLine(uint8_t x, uint8_t y, uint8_t h, _Bool color)
{
  SSD1306_DrawLine(x, y, x, y + h - 1, color);
}


void SSD1306_FillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, _Bool color)
{
  for (int16_t i = x; i < x + w; i++)
    SSD1306_DrawFastVLine(i, y, h, color);
}

void SSD1306_DrawCircle(int16_t x0, int16_t y0, int16_t r)
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  SSD1306_DrawPixel(x0  , y0 + r, 1);
  SSD1306_DrawPixel(x0  , y0 - r, 1);
  SSD1306_DrawPixel(x0 + r, y0, 1);
  SSD1306_DrawPixel(x0 - r, y0, 1);

  while (x < y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    SSD1306_DrawPixel(x0 + x, y0 + y, 1);
    SSD1306_DrawPixel(x0 - x, y0 + y, 1);
    SSD1306_DrawPixel(x0 + x, y0 - y, 1);
    SSD1306_DrawPixel(x0 - x, y0 - y, 1);
    SSD1306_DrawPixel(x0 + y, y0 + x, 1);
    SSD1306_DrawPixel(x0 - y, y0 + x, 1);
    SSD1306_DrawPixel(x0 + y, y0 - x, 1);
    SSD1306_DrawPixel(x0 - y, y0 - x, 1);
  }

}

void SSD1306_DrawRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
  SSD1306_DrawFastHLine(x, y, w, 1);
  SSD1306_DrawFastHLine(x, y + h - 1, w, 1);
  SSD1306_DrawFastVLine(x, y, h, 1);
  SSD1306_DrawFastVLine(x + w - 1, y, h, 1);
}

void SSD1306_DrawTriangle(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
  SSD1306_DrawLine(x0, y0, x1, y1, 1);
  SSD1306_DrawLine(x1, y1, x2, y2, 1);
  SSD1306_DrawLine(x2, y2, x0, y0, 1);
}

void SSD1306_GotoXY(uint8_t x, uint8_t y)
{
  if((x >= SSD1306_LCDWIDTH) || (y >= SSD1306_LCDHEIGHT))
    return;
  x_pos = x;
  y_pos = y;
}

void SSD1306_TextSize(uint8_t t_size)
{
  if(t_size < 1)
    t_size = 1;
  text_size = t_size;
}

void SSD1306_Print(uint8_t c)
{
  _Bool _color;
  uint8_t i, j, line;

  if (c == ' ' && x_pos == 0)
    return;
  if(c == '\a') {
    x_pos = y_pos = 0;
    return;
  }
  if( (c == '\b') && (x_pos >= text_size * 6) ) {
    x_pos -= text_size * 6;
    return;
  }
  if(c == '\r') {
    x_pos = 0;
    return;
  }
  if(c == '\n') {
    y_pos += text_size * 8;
    if((y_pos + text_size * 7) > SSD1306_LCDHEIGHT)
      y_pos = 0;
    return;
  }

  if((c < ' ') || (c > '~'))
    c = '?';

  for(i = 0; i < 5; i++ ) {
    if(c < 'S')
      line = Font_Part_A[(c - ' ') * 5 + i];
    else
      line = Font_Part_B[(c - 'S') * 5 + i];

    for(j = 0; j < 7; j++, line >>= 1) {
      if(line & 0x01)
        _color = 1;
      else
        _color = 0;
      if(text_size == 1) SSD1306_DrawPixel(x_pos + i, y_pos + j, _color);
      else               SSD1306_FillRect(x_pos + (i * text_size), y_pos + (j * text_size), text_size, text_size, _color);
    }
  }

  SSD1306_FillRect(x_pos + (5 * text_size), y_pos, text_size, 7 * text_size, 0);

  x_pos += text_size * 6;

  if( x_pos > (SSD1306_LCDWIDTH + text_size * 6) )
    x_pos = SSD1306_LCDWIDTH;

  if (1 && (x_pos + (text_size * 5)) > SSD1306_LCDWIDTH)
  {
    x_pos = 0;
    y_pos += text_size * 8;
    if((y_pos + text_size * 7) > SSD1306_LCDHEIGHT)
      y_pos = 0;
  }
}

void SSD1306_DrawText(uint8_t x, uint8_t y, char *_text, uint8_t size)
{
  SSD1306_GotoXY(x, y);
  SSD1306_TextSize(size);
  while(*_text != '\0')
    SSD1306_Print(*_text++);

}

#define pgm_read_byte(addr) \
 (*(const unsigned char *)(addr))

void SSD1306_ROMBMP(uint8_t x, uint8_t y, uint8_t *bitmap, uint8_t w, uint8_t h)
{
	int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
	uint8_t byte = 0;

	for(int16_t j=0; j<h; j++, y++) {
	    for(int16_t i=0; i<w; i++) {
	        if(i & 7) byte <<= 1;
	        else      byte   = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
	        if(byte & 0x80) SSD1306_DrawPixel(x+i, y, 1);
	    }
	}
}

void SSD1306_INVERSE(uint8_t x, uint8_t y, uint8_t x0, uint8_t y0){
	for(; x <= x0; x++){
		for(uint8_t j = y; j <= y0; j++){
			ssd1306_buffer[x + (j/8)*SSD1306_LCDWIDTH ] ^=  (1 << (j&7));
		}
	}
}

void SSD1306_Page2Page (uint8_t p1, uint8_t p2)
{
	au8OLED_Leght[enControlByte] = 0x00;

	au8OLED_Leght[enCommandByte] = SSD1306_PAGEADDR;
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);
	au8OLED_Leght[enCommandByte] = p1;								// Page start address (0 = reset)
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);
	au8OLED_Leght[enCommandByte] = p2;									// Page end address
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);

	au8OLED_Leght[enCommandByte] = SSD1306_COLUMNADDR;
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);
	au8OLED_Leght[enCommandByte] = 0x00;								// Column start address (0 = reset)
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);
	au8OLED_Leght[enCommandByte] = SSD1306_LCDWIDTH  - 1;				// Column end address (127 = reset)
	 I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);

	for (uint16_t i = (p1 * 128); i < ((p2+1) * 128); i++){
    // send a bunch of data in one mission
	au8OLED_Leght[enControlByte] = SSD1306_SETSTARTLINE;
	au8OLED_Leght[enCommandByte] = ssd1306_buffer[i];
     I2C_vfnSendData (&au8OLED_Leght[0], Message_Leght);
	}
}





