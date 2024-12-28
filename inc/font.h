#ifndef __FONT_H
#define __FONT_H

#include <stdint.h>

#define FONT_20x32_WIDTH 20
#define FONT_20x32_HEIGHT 32
#define FONT_8x16_WIDTH 8
#define FONT_8x16_HEIGHT 16

extern const uint8_t font_20x32[][80];
extern const uint8_t font_8x16[][16];

#endif /* __FONT_H */
