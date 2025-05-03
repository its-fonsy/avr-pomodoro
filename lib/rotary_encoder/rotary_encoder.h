#ifndef __ROTARY_ENCODER_H
#define __ROTARY_ENCODER_H

#include <stdint.h>

enum {
    ROTARY_ENCODER_IDLE,
    ROTARY_ENCODER_CW,
    ROTARY_ENCODER_CCW,
};

enum {
    ROTARY_ENCODER_UNLOCKED,
    ROTARY_ENCODER_LOCKED
};

typedef struct {
    uint8_t (*read_pinA)(void);
    uint8_t (*read_pinB)(void);
    uint8_t history;
    uint8_t state;
    uint8_t lock;
} rotary_encoder_t;

void rotary_encoder_init(rotary_encoder_t* rotary);
void rotary_encoder_update(rotary_encoder_t* rotary);
uint8_t rotary_encoder_is_turned(rotary_encoder_t* rotary);

#endif /* __ROTARY_ENCODER_H */
