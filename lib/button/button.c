#include "button.h"
#include <stdint.h>

void button_init(button_t* button)
{
    button->history = 0xFF;
    button->status = BUTTON_IDLE;
    button->lock = BUTTON_UNLOCKED;
}

void button_update(button_t* button)
{
    if (button->lock == BUTTON_LOCKED || button->status == BUTTON_PRESSED)
        return;

    button->lock = BUTTON_LOCKED;

    button->history <<= 1;
    button->history |= button->read_pin();

    if (button->status == BUTTON_IDLE && button->history == 0x00)
        button->status = BUTTON_PRESSED;
    else if (button->status == BUTTON_PRESS_ACK && button->history == 0xFF)
        button->status = BUTTON_IDLE;

    button->lock = BUTTON_UNLOCKED;
}

void button_reset(button_t* button)
{
    while (button->lock == BUTTON_LOCKED) { }

    button->lock = BUTTON_LOCKED;
    button->status = BUTTON_IDLE;
    button->lock = BUTTON_UNLOCKED;
}

uint8_t button_is_pressed(button_t* button)
{
    uint8_t ret;

    ret = 0;

    if (button->lock == BUTTON_LOCKED)
        return ret;

    button->lock = BUTTON_LOCKED;
    if (button->status == BUTTON_PRESSED) {
        button->status = BUTTON_PRESS_ACK;
        ret = 1;
    }
    button->lock = BUTTON_UNLOCKED;

    return ret;
}
