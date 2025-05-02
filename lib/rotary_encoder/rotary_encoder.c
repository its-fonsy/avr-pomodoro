#include "rotary_encoder.h"

void rotary_encoder_init(rotary_encoder_t* rotary)
{
    rotary->history = 0;
    rotary->state = ROTARY_ENCODER_IDLE;
    rotary->lock = ROTARY_ENCODER_UNLOCKED;
}

void rotary_encoder_update(rotary_encoder_t* rotary)
{
    if (rotary->state != ROTARY_ENCODER_IDLE || rotary->lock == ROTARY_ENCODER_LOCKED)
        return;

    rotary->lock = ROTARY_ENCODER_LOCKED;

    rotary->history <<= 2;
    rotary->history |= rotary->read_pinA() ? 0x01 : 0x00;
    rotary->history |= rotary->read_pinB() ? 0x02 : 0x00;

    if (rotary->history == 0xFD)
        rotary->state = ROTARY_ENCODER_CW;
    if (rotary->history == 0xFE)
        rotary->state = ROTARY_ENCODER_CCW;

    rotary->lock = ROTARY_ENCODER_UNLOCKED;
}
