#include <avr/io.h>
#include <stdint.h>

#include "gpio.h"

void gpio_init(void)
{
    /* Button initialization */
    DDRB &= ~(_BV(BUTTON_PIN));
    PORTB |= _BV(BUTTON_PIN);

    /* Rotary encoder GPIO as input */
    DDRB &= ~(_BV(ROT_ENC_PINA));
    DDRB &= ~(_BV(ROT_ENC_PINB));

    /* Rotary encoder Ensure PULL-UP is disabled */
    PORTB &= ~(_BV(ROT_ENC_PINA));
    PORTB &= ~(_BV(ROT_ENC_PINB));
}

uint8_t gpio_button_read(void)
{
    return bit_is_set(PINB, BUTTON_PIN) ? 0x01 : 0x00;
}

uint8_t rot_enc_read_pinA(void)
{
    return bit_is_set(PINB, ROT_ENC_PINA) ? 0x01 : 0x00;
}

uint8_t rot_enc_read_pinB(void)
{
    return bit_is_set(PINB, ROT_ENC_PINB) ? 0x01 : 0x00;
}
