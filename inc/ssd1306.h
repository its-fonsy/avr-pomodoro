#ifndef __SSD1306_H
#define __SSD1306_H

#include <stdint.h>

#define DISPLAY_HEIGHT 32
#define DISPLAY_WIDTH 128

#define SSD1306_I2C_ADDRESS 0x3C
#define SSD1306_CO_BIT 0x80
#define SSD1306_DC_BIT 0x40

/* Fundamental Command */

#define SSD1306_CMD_SET_CONTRAST_CONTROL 0x81
#define SSD1306_CMD_ENTIRE_DISPLAY_ON_FOLLOW_RAM 0xA4
#define SSD1306_CMD_ENTIRE_DISPLAY_ON_IGNORE_RAM 0xA5
#define SSD1306_CMD_SET_DISPLAY_NORMAL 0xA6
#define SSD1306_CMD_SET_DISPLAY_INVERSE 0xA7
#define SSD1306_CMD_SET_DISPLAY_ON 0xAE
#define SSD1306_CMD_SET_DISPLAY_OFF 0xAF

/* Scrolling Command */

#define SSD1306_CMD_CONTINUOUS_HORIZONTAL_SCROLL_RIGHT 0x26
#define SSD1306_CMD_CONTINUOUS_HORIZONTAL_SCROLL_LEFT 0x27
#define SSD1306_CMD_CONTINUOUS_VERTICAL_AND_HORIZONTAL_SCROLL_RIGHT 0x29
#define SSD1306_CMD_CONTINUOUS_VERTICAL_AND_HORIZONTAL_SCROLL_LEFT 0x2A
#define SSD1306_CMD_DEACTIVATE_SCROLL 0x2E
#define SSD1306_CMD_ACTIVATE_SCROLL 0x2F
#define SSD1306_CMD_SET_VERTICAL_SCROLL_AREA 0xA3

/* Scrolling Constants */

#define SSD1306_SCROLL_LEFT 0x00
#define SSD1306_SCROLL_RIGHT 0x01

#define SSD1306_CONTINUOUS_SCROLL_PAGE0 0x00
#define SSD1306_CONTINUOUS_SCROLL_PAGE1 0x01
#define SSD1306_CONTINUOUS_SCROLL_PAGE2 0x02
#define SSD1306_CONTINUOUS_SCROLL_PAGE3 0x03
#define SSD1306_CONTINUOUS_SCROLL_PAGE4 0x04
#define SSD1306_CONTINUOUS_SCROLL_PAGE5 0x05
#define SSD1306_CONTINUOUS_SCROLL_PAGE6 0x06
#define SSD1306_CONTINUOUS_SCROLL_PAGE7 0x07

#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_5 0x00
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_64 0x01
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_128 0x02
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_256 0x03
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_3 0x04
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_4 0x05
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_25 0x06
#define SSD1306_CONTINUOUS_SCROLL_FRAME_INTERVAL_2 0x07

/* Addressing Setting Command */

#define SSD1306_CMD_SET_LO_COL_START_ADD 0x00
#define SSD1306_CMD_SET_HI_COL_START_ADD 0x10
#define SSD1306_CMD_SET_MEM_ADDRESSING_MODE 0x20
#define SSD1306_CMD_SET_COL_ADDRESS 0x21
#define SSD1306_CMD_SET_PAGE_ADDRESS 0x22
#define SSD1306_CMD_SET_PAGE_START_ADDR 0xB0

/* Addressing Setting Constants */

#define SSD1306_ADDRESSING_MODE_HORIZONTAL 0x00
#define SSD1306_ADDRESSING_MODE_VERTICAL 0x01
#define SSD1306_ADDRESSING_MODE_PAGE 0x02

/* Hardware Configuration Command */

#define SSD1306_CMD_SET_DISPLAY_START_LINE 0x40
#define SSD1306_CMD_MAP_SEG0_TO_COL_0 0xA0
#define SSD1306_CMD_MAP_SEG0_TO_COL_127 0xA1
#define SSD1306_CMD_SET_MULTIPLEX_RATIO 0xA8
#define SSD1306_CMD_SET_NORMAL_MODE_COM_OUTPUT_SCAN_DIRECTION 0xC0
#define SSD1306_CMD_SET_REMAPPED_MODE_COM_OUTPUT_SCAN_DIRECTION 0xC8
#define SSD1306_CMD_SET_DISPLAY_OFFSET 0xD3
#define SSD1306_CMD_SET_COM_PINS_HW_CONF 0xDA

/* Hardware Configuration Constants */

#define SSD1306_MAP_SEG0_TO_COL_0 0
#define SSD1306_MAP_SEG0_TO_COL_127 1
#define SSD1306_COM_NORMAL_MODE_SCAN 0
#define SSD1306_COM_REMAPPED_MODE_SCAN 1
#define SSD1306_COM_PIN_CFG_SEQUENTIAL 0x00
#define SSD1306_COM_PIN_CFG_ALTERNATIVE 0x10
#define SSD1306_COM_LEFT_RIGHT_REMAP_DISABLE 0x10
#define SSD1306_COM_LEFT_RIGHT_REMAP_ENABLE 0x20

/* Timing and Driving Scheme Setting Command */

#define SSD1306_CMD_SET_DISPLAY_CK_RATIO_AND_OSC 0xD5
#define SSD1306_CMD_SET_PRE_CHRG_PERIOD 0xD9
#define SSD1306_CMD_SET_VCOMH 0xDB
#define SSD1306_CMD_NOP 0xE3

/* Timing and Driving Scheme Setting Constants */

#define SSD1306_VCOMH_0_65VCC 0x00
#define SSD1306_VCOMH_0_77VCC 0x20
#define SSD1306_VCOMH_0_83VCC 0x30

/* Charge Pump Command */

#define SSD1306_CMD_CHARGE_PUMP_SET 0x8D

/* Charge Pump Constants */

#define SSD1306_CHARGE_PUMP_DISABLED 0x10
#define SSD1306_CHARGE_PUMP_ENABLED 0x14

/* Low level device control functions */

uint8_t ssd1306_write_gddram (uint8_t* data, uint8_t size);
uint8_t ssd1306_cmd (uint8_t cmd);
uint8_t ssd1306_cmd_and_data (uint8_t cmd, uint8_t *data, uint32_t data_size);
uint8_t ssd1306_set_contrast (uint8_t contrast);
uint8_t ssd1306_continuous_horizontal_scroll_setup (uint8_t direction,
                                                    uint8_t start_page,
                                                    uint8_t frame_interval,
                                                    uint8_t end_page);
uint8_t ssd1306_continuous_vertical_and_horizontal_scroll_setup (
    uint8_t direction, uint8_t start_page, uint8_t frame_interval,
    uint8_t end_page, uint8_t vertical_offset);
uint8_t ssd1306_set_vertical_scroll_area (uint8_t row_fixed_area,
                                          uint8_t row_scroll_area);
uint8_t ssd1306_deactivate_scroll ();
uint8_t ssd1306_activate_scroll ();
uint8_t ssd1306_set_lower_col_start_addr (uint8_t addr);
uint8_t ssd1306_set_higher_col_start_addr (uint8_t addr);
uint8_t ssd1306_set_memory_addressing_mode (uint8_t mode);
uint8_t ssd1306_set_col_address (uint8_t start, uint8_t end);
uint8_t ssd1306_set_page_address (uint8_t start, uint8_t end);
uint8_t ssd1306_set_page_start_address (uint8_t start);
uint8_t ssd1306_set_display_start_line (uint8_t start);
uint8_t ssd1306_set_segment_remap (uint8_t map);
uint8_t ssd1306_set_multiplex_ratio (uint8_t ratio);
uint8_t ssd1306_set_com_mode (uint8_t mode);
uint8_t ssd1306_set_display_offset (uint8_t offset);
uint8_t ssd1306_com_pin_hw_conf (uint8_t com_pin_conf,
                                 uint8_t left_right_remap);
uint8_t ssd1306_set_display_clock_and_osc (uint8_t ck, uint8_t osc);
uint8_t ssd1306_set_precharge_period (uint8_t phase1, uint8_t phase2);
uint8_t ssd1306_set_vcomh (uint8_t level);
uint8_t ssd1306_set_charge_pump (uint8_t status);
uint8_t ssd1306_nop ();

/* High level functions */

void ssd1306_init ();

#endif /* __SSD1306_H */