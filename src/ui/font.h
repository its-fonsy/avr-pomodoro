#ifndef __FONT_H
#define __FONT_H

#include <stdint.h>

#define FONT_20x32_WIDTH 20
#define FONT_20x32_HEIGHT 32
#define FONT_8x16_WIDTH 8
#define FONT_8x16_HEIGHT 16

#define WORD_MAX_SIZE 8

typedef struct {
    uint8_t graphic_lut[WORD_MAX_SIZE];
    uint8_t graphic_size[WORD_MAX_SIZE];
    uint8_t size;
    const uint8_t** base_array;
} graphic_t;

extern const uint8_t numbers_32px[][80];
extern const uint8_t timer_dot[10];
extern const uint8_t* numbers_8px[];

extern const graphic_t pause_8px;
extern const graphic_t work_8px;
extern const graphic_t timer_8px;
extern const graphic_t start_8px;
extern const graphic_t set_8px;
extern const graphic_t right_arrow_8px;
extern const graphic_t left_selector_8px;
extern const graphic_t right_selector_8px;
extern const graphic_t dots_8px;

extern const graphic_t work_16px;
extern const graphic_t pause_16px;
extern const graphic_t finished_16px;

#endif /* __FONT_H */
