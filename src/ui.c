#include "ssd1306.h"
#include "font.h"
#include "ui.h"

void ui_draw_minutes(uint8_t n)
{
  uint8_t unit;
  uint8_t tens;

  unit = n % 10;
  tens = n / 10;

  /* Draw tens digit */

  ssd1306_addressing_border(FONT_MINUTES_X,
                            FONT_MINUTES_X + FONT_WIDTH - 1,
                            0,
                            3);
  ssd1306_data((uint8_t *) font_24x32[tens], sizeof(font_24x32[tens]));

  /* Draw unit digit */

  ssd1306_addressing_border(FONT_MINUTES_X + FONT_WIDTH + FONT_OFFSET,
                            FONT_MINUTES_X + FONT_OFFSET + 2*FONT_WIDTH - 1,
                            0,
                            3);
  ssd1306_data((uint8_t *) font_24x32[unit], sizeof(font_24x32[unit]));
}

void ui_draw_seconds(uint8_t n)
{
  uint8_t unit;
  uint8_t tens;

  unit = n % 10;
  tens = n / 10;

  /* Draw tens digit */

  ssd1306_addressing_border(FONT_SECONDS_X,
                            FONT_SECONDS_X + FONT_WIDTH - 1,
                            0,
                            3);
  ssd1306_data((uint8_t *) font_24x32[tens], sizeof(font_24x32[tens]));

  /* Draw unit digit */

  ssd1306_addressing_border(FONT_SECONDS_X + FONT_WIDTH + FONT_OFFSET,
                            FONT_SECONDS_X + FONT_WIDTH + FONT_OFFSET + FONT_WIDTH - 1,
                            0,
                            3);
  ssd1306_data((uint8_t *) font_24x32[unit], sizeof(font_24x32[unit]));
}

void ui_draw_dots()
{
  uint8_t dot[] = {
    0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x07
  };

  ssd1306_addressing_border(FONT_DOTS_X,
                            FONT_DOTS_X + FONT_DOT_WIDTH - 1,
                            0,
                            3);
  ssd1306_data(dot, sizeof(dot));

  ssd1306_addressing_border(FONT_DOTS_X,
                            FONT_DOTS_X + FONT_DOT_WIDTH - 1,
                            2,
                            3);
  ssd1306_data(dot, sizeof(dot));

}

