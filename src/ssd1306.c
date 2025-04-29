#include "ssd1306.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void ssd1306_init(ssd1306_t* display)
{
    uint8_t cmd[] = {
        SSD1306_CMD_SET_DISPLAY_OFF,
        SSD1306_CMD_SET_MEM_ADDRESSING_MODE, SSD1306_ADDRESSING_MODE_HORIZONTAL,
        SSD1306_CMD_SET_PAGE_START_ADDR,
        SSD1306_CMD_SET_REMAPPED_MODE_COM_OUTPUT_SCAN_DIRECTION,
        SSD1306_CMD_SET_LO_COL_START_ADD | 0x00,
        SSD1306_CMD_SET_HI_COL_START_ADD | 0x00,
        SSD1306_CMD_SET_DISPLAY_START_LINE,
        SSD1306_CMD_SET_CONTRAST_CONTROL, 63,
        SSD1306_CMD_MAP_SEG0_TO_COL_127,
        SSD1306_CMD_SET_DISPLAY_NORMAL,
        SSD1306_CMD_SET_MULTIPLEX_RATIO, (DISPLAY_HEIGHT - 1),
        SSD1306_CMD_ENTIRE_DISPLAY_ON_FOLLOW_RAM,
        SSD1306_CMD_SET_DISPLAY_OFFSET, 0x00,
        SSD1306_CMD_SET_DISPLAY_CK_RATIO_AND_OSC, 0xF0,
        SSD1306_CMD_SET_PRE_CHRG_PERIOD, 0x22,
        SSD1306_CMD_SET_COM_PINS_HW_CONF, (SSD1306_COM_PIN_CFG_SEQUENTIAL | SSD1306_COM_LEFT_RIGHT_REMAP_DISABLE),
        SSD1306_CMD_SET_VCOMH, SSD1306_VCOMH_0_77VCC,
        SSD1306_CMD_CHARGE_PUMP_SET, SSD1306_CHARGE_PUMP_ENABLED,
        SSD1306_CMD_SET_DISPLAY_ON
    };

    ssd1306_cmd(display, cmd, sizeof(cmd));

    return;
}

void ssd1306_cmd(ssd1306_t* display, uint8_t* cmd, uint32_t size)
{
    uint8_t* i2c_packet;
    uint32_t i2c_packet_size;

    i2c_packet_size = size + 1;
    i2c_packet = (uint8_t*)malloc(sizeof(uint8_t) * i2c_packet_size);
    i2c_packet[0] = SSD1306_CTRL_BYTE_CMD;
    memcpy(i2c_packet + 1, cmd, size);

    display->i2c_write(display->i2c_address, i2c_packet, i2c_packet_size);

    free(i2c_packet);
}

void ssd1306_data(ssd1306_t* display, uint8_t* data, uint32_t size)
{
    uint8_t* i2c_packet;
    uint32_t i2c_packet_size;

    i2c_packet_size = size + 1;
    i2c_packet = (uint8_t*)malloc(sizeof(uint8_t) * i2c_packet_size);
    i2c_packet[0] = SSD1306_CTRL_BYTE_DATA;
    memcpy(i2c_packet + 1, data, size);

    display->i2c_write(display->i2c_address, i2c_packet, i2c_packet_size);

    free(i2c_packet);
}

void ssd1306_goto(ssd1306_t* display, uint8_t column, uint8_t page)
{
    uint8_t cmd[] = {
        SSD1306_CMD_SET_PAGE_START_ADDR + page,
        SSD1306_CMD_SET_COL_ADDRESS, column, DISPLAY_WIDTH - 1
    };

    ssd1306_cmd(display, cmd, sizeof(cmd));
}

void ssd1306_clear_screen(ssd1306_t* display)
{
    uint8_t i;
    uint8_t zeros[DISPLAY_WIDTH] = { 0 };

    for (i = 0; i < DISPLAY_HEIGHT / 8; i++) {
        ssd1306_goto(display, 0, i);
        ssd1306_data(display, zeros, sizeof(zeros));
    }
}

void ssd1306_set_column_and_page_address_boundary(
    ssd1306_t* display, ssd1306_address_boundary_t column, ssd1306_address_boundary_t page)
{
    uint8_t cmd[] = {
        SSD1306_CMD_SET_COL_ADDRESS, column.start, column.end,
        SSD1306_CMD_SET_PAGE_ADDRESS, page.start, page.end
    };

    ssd1306_cmd(display, cmd, sizeof(cmd));
}

void ssd1306_set_column_address_boundary(ssd1306_t* display, uint8_t start, uint8_t end)
{
    uint8_t cmd[] = { SSD1306_CMD_SET_COL_ADDRESS, start, end };
    ssd1306_cmd(display, cmd, sizeof(cmd));
}

void ssd1306_set_page_address_boundary(ssd1306_t* display, uint8_t start, uint8_t end)
{
    uint8_t cmd[] = { SSD1306_CMD_SET_PAGE_ADDRESS, start, end };
    ssd1306_cmd(display, cmd, sizeof(cmd));
}
