#ifndef __FONT_H
#define __FONT_H

#include <stdint.h>

#define FONT_20x32_WIDTH 20
#define FONT_20x32_HEIGHT 32
#define FONT_8x16_WIDTH 8
#define FONT_8x16_HEIGHT 16

#define WORD_MAX_SIZE 5

typedef struct {
    uint8_t graphic_lut[WORD_MAX_SIZE];
    uint8_t graphic_size[WORD_MAX_SIZE];
    uint8_t size;
    const uint8_t** base_array;
} graphic_t;

extern const uint8_t font_20x32[][80];
extern const uint8_t font_8x16[][16];
extern const uint8_t* hmpg_letters[];
extern const uint8_t* numbers_6x8[];

extern const graphic_t pause;
extern const graphic_t work;
extern const graphic_t timer;
extern const graphic_t right_arrow;

#endif /* __FONT_H */
