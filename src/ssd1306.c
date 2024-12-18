#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "i2c.h"
#include "ssd1306.h"

void
ssd1306_init ()
{
  ssd1306_cmd (SSD1306_CMD_SET_DISPLAY_ON);
  ssd1306_set_memory_addressing_mode (SSD1306_ADDRESSING_MODE_HORIZONTAL);
  ssd1306_set_page_start_address (0);
  ssd1306_set_com_mode (SSD1306_COM_REMAPPED_MODE_SCAN);
  ssd1306_set_lower_col_start_addr (0);
  ssd1306_set_higher_col_start_addr (0);
  ssd1306_set_display_start_line (0);
  ssd1306_set_contrast (63);
  ssd1306_set_segment_remap (SSD1306_MAP_SEG0_TO_COL_127);
  ssd1306_cmd (SSD1306_CMD_SET_DISPLAY_NORMAL);
  ssd1306_set_multiplex_ratio (DISPLAY_HEIGHT - 1);
  ssd1306_cmd (SSD1306_CMD_ENTIRE_DISPLAY_ON_FOLLOW_RAM);
  ssd1306_set_display_offset (0);
  ssd1306_set_display_clock_and_osc (0, 15);
  ssd1306_set_precharge_period (2, 2);
  ssd1306_com_pin_hw_conf (SSD1306_COM_PIN_CFG_SEQUENTIAL,
                           SSD1306_COM_LEFT_RIGHT_REMAP_DISABLE);
  ssd1306_set_vcomh (SSD1306_VCOMH_0_77VCC);
  ssd1306_set_charge_pump(SSD1306_CHARGE_PUMP_ENABLED);
}

uint8_t
ssd1306_write_gddram (uint8_t *data, uint8_t size)
{
  uint8_t addr;
  uint8_t sze;
  uint8_t ret = 0;
  uint8_t *packet;

  sze = size + 1;
  packet = (uint8_t *)malloc (sizeof (uint8_t) * sze);

  addr = (SSD1306_I2C_ADDRESS << 1);
  packet[0] = SSD1306_CO_BIT;
  memcpy (packet + 1, data, size);

  ret = i2c_send (addr, packet, sze);

  return ret;
}

uint8_t
ssd1306_cmd (uint8_t cmd)
{
  uint8_t addr;
  uint8_t ret = 0;
  uint8_t data[] = { (SSD1306_CO_BIT | SSD1306_DC_BIT), cmd };

  addr = (SSD1306_I2C_ADDRESS << 1);
  ret = i2c_send (addr, data, 2);

  return ret;
}

uint8_t
ssd1306_cmd_and_data (uint8_t cmd, uint8_t *data, uint32_t data_size)
{
  uint8_t addr;
  uint8_t ret = 0;
  uint8_t cmd_and_data_size;
  uint8_t *cmd_and_data;

  cmd_and_data_size = data_size + 2;
  cmd_and_data = (uint8_t *)malloc (sizeof (uint8_t) * cmd_and_data_size);

  cmd_and_data[0] = SSD1306_CO_BIT | SSD1306_DC_BIT;
  cmd_and_data[1] = cmd;
  memcpy (cmd_and_data + 2, data, data_size);

  addr = (SSD1306_I2C_ADDRESS << 1);
  ret = i2c_send (addr, cmd_and_data, cmd_and_data_size);

  free (cmd_and_data);

  return ret;
}

uint8_t
ssd1306_set_contrast (uint8_t contrast)
{
  uint8_t ret = 0;

  ret = ssd1306_cmd_and_data (SSD1306_CMD_SET_CONTRAST_CONTROL, &contrast, 1);

  return ret;
}

uint8_t
ssd1306_continuous_horizontal_scroll_setup (uint8_t direction,
                                            uint8_t start_page,
                                            uint8_t frame_interval,
                                            uint8_t end_page)
{
  uint8_t ret = 0;
  uint8_t cmd;
  uint8_t data[] = { 0x00, start_page, frame_interval, end_page, 0x00, 0xFF };

  if (direction == SSD1306_SCROLL_LEFT)
    cmd = SSD1306_CMD_CONTINUOUS_HORIZONTAL_SCROLL_LEFT;
  else
    cmd = SSD1306_CMD_CONTINUOUS_HORIZONTAL_SCROLL_RIGHT;

  ret = ssd1306_cmd_and_data (cmd, data, 6);

  return ret;
}

uint8_t
ssd1306_continuous_vertical_and_horizontal_scroll_setup (
    uint8_t direction, uint8_t start_page, uint8_t frame_interval,
    uint8_t end_page, uint8_t vertical_offset)
{
  uint8_t ret = 0;
  uint8_t cmd;
  uint8_t data[]
      = { 0x00, start_page, frame_interval, end_page, vertical_offset };

  if (direction == SSD1306_SCROLL_LEFT)
    cmd = SSD1306_CMD_CONTINUOUS_VERTICAL_AND_HORIZONTAL_SCROLL_LEFT;
  else
    cmd = SSD1306_CMD_CONTINUOUS_VERTICAL_AND_HORIZONTAL_SCROLL_RIGHT;

  ret = ssd1306_cmd_and_data (cmd, data, 5);

  return ret;
}

uint8_t
ssd1306_deactivate_scroll ()
{
  uint8_t ret = 0;

  ret = ssd1306_cmd (SSD1306_CMD_DEACTIVATE_SCROLL);

  return ret;
}

uint8_t
ssd1306_activate_scroll ()
{
  uint8_t ret = 0;

  ret = ssd1306_cmd (SSD1306_CMD_ACTIVATE_SCROLL);

  return ret;
}

uint8_t
ssd1306_set_vertical_scroll_area (uint8_t row_fixed_area,
                                  uint8_t row_scroll_area)
{
  uint8_t ret = 0;
  uint8_t data[] = { row_fixed_area, row_scroll_area };

  ret = ssd1306_cmd_and_data (SSD1306_CMD_SET_VERTICAL_SCROLL_AREA, data, 2);

  return ret;
}

uint8_t
ssd1306_set_lower_col_start_addr (uint8_t addr)
{
  uint8_t ret = 0;
  uint8_t cmd;

  cmd = SSD1306_CMD_SET_LO_COL_START_ADD | (addr & 0x0F);
  ret = ssd1306_cmd (cmd);

  return ret;
}

uint8_t
ssd1306_set_higher_col_start_addr (uint8_t addr)
{
  uint8_t ret = 0;
  uint8_t cmd;

  cmd = SSD1306_CMD_SET_HI_COL_START_ADD | (addr & 0x0F);
  ret = ssd1306_cmd (cmd);

  return ret;
}

uint8_t
ssd1306_set_memory_addressing_mode (uint8_t mode)
{
  uint8_t ret = 0;

  ret = ssd1306_cmd_and_data (SSD1306_CMD_SET_MEM_ADDRESSING_MODE, &mode, 1);

  return ret;
}

uint8_t
ssd1306_set_col_address (uint8_t start, uint8_t end)
{
  uint8_t ret = 0;
  uint8_t data[] = { start, end };

  ret = ssd1306_cmd_and_data (SSD1306_CMD_SET_COL_ADDRESS, data, 2);

  return ret;
}

uint8_t
ssd1306_set_page_address (uint8_t start, uint8_t end)
{
  uint8_t ret = 0;
  uint8_t data[] = { start, end };

  ret = ssd1306_cmd_and_data (SSD1306_CMD_SET_PAGE_ADDRESS, data, 2);

  return ret;
}

uint8_t
ssd1306_set_page_start_address (uint8_t start)
{
  uint8_t ret = 0;
  uint8_t cmd;

  cmd = SSD1306_CMD_SET_PAGE_START_ADDR | (start & 0x07);
  ret = ssd1306_cmd (cmd);

  return ret;
}

uint8_t
ssd1306_set_display_start_line (uint8_t start)
{
  uint8_t ret = 0;
  uint8_t cmd;

  cmd = SSD1306_CMD_SET_DISPLAY_START_LINE | (start & 0x3F);
  ret = ssd1306_cmd (cmd);

  return ret;
}

uint8_t
ssd1306_set_segment_remap (uint8_t map)
{
  uint8_t ret = 0;
  uint8_t cmd;

  if (map == SSD1306_MAP_SEG0_TO_COL_0)
    cmd = SSD1306_CMD_MAP_SEG0_TO_COL_0;
  else
    cmd = SSD1306_CMD_MAP_SEG0_TO_COL_127;

  ret = ssd1306_cmd (cmd);

  return ret;
}

uint8_t
ssd1306_set_multiplex_ratio (uint8_t ratio)
{
  uint8_t ret = 0;

  ret = ssd1306_cmd_and_data (SSD1306_CMD_SET_MULTIPLEX_RATIO, &ratio, 1);

  return ret;
}

uint8_t
ssd1306_set_com_mode (uint8_t mode)
{
  uint8_t ret = 0;
  uint8_t cmd;

  if (mode == SSD1306_COM_NORMAL_MODE_SCAN)
    cmd = SSD1306_CMD_SET_NORMAL_MODE_COM_OUTPUT_SCAN_DIRECTION;
  else
    cmd = SSD1306_CMD_SET_REMAPPED_MODE_COM_OUTPUT_SCAN_DIRECTION;

  ret = ssd1306_cmd (cmd);

  return ret;
}

uint8_t
ssd1306_set_display_offset (uint8_t offset)
{
  uint8_t ret = 0;

  ret = ssd1306_cmd_and_data (SSD1306_CMD_SET_DISPLAY_OFFSET, &offset, 1);

  return ret;
}

uint8_t
ssd1306_com_pin_hw_conf (uint8_t com_pin_conf, uint8_t left_right_remap)
{
  uint8_t ret = 0;
  uint8_t data = 0;

  data = com_pin_conf | left_right_remap | 0x02;

  ret = ssd1306_cmd_and_data (SSD1306_CMD_SET_DISPLAY_OFFSET, &data, 1);

  return ret;
}

uint8_t
ssd1306_set_display_clock_and_osc (uint8_t ck, uint8_t osc)
{
  uint8_t ret = 0;
  uint8_t data;

  /* First nibble is CK, second nibble is Oscillator */

  data = (ck & 0x0F) | ((osc << 4) & 0xF0);
  ret = ssd1306_cmd_and_data (SSD1306_CMD_SET_DISPLAY_CK_RATIO_AND_OSC, &data,
                              1);

  return ret;
}

uint8_t
ssd1306_set_precharge_period (uint8_t phase1, uint8_t phase2)
{
  uint8_t ret = 0;
  uint8_t data;

  data = (phase1 & 0x0F) | ((phase2 << 4) & 0xF0);
  ret = ssd1306_cmd_and_data (SSD1306_CMD_SET_PRE_CHRG_PERIOD, &data, 1);

  return ret;
}

uint8_t
ssd1306_set_vcomh (uint8_t level)
{
  uint8_t ret = 0;

  ret = ssd1306_cmd_and_data (SSD1306_CMD_SET_VCOMH, &level, 1);

  return ret;
}

uint8_t
ssd1306_set_charge_pump (uint8_t status)
{
  uint8_t ret = 0;

  ret = ssd1306_cmd_and_data(SSD1306_CMD_CHARGE_PUMP_SET, &status, 1);

  return ret;
}

uint8_t
ssd1306_nop ()
{
  uint8_t ret = 0;

  ret = ssd1306_cmd (SSD1306_CMD_NOP);

  return ret;
}
