#ifndef __GPIO_H
#define __GPIO_H

#include <stdint.h>

#define BUTTON_PIN PB4
#define ROT_ENC_PINA PB0
#define ROT_ENC_PINB PB1

void gpio_init(void);
uint8_t gpio_button_read(void);
uint8_t rot_enc_read_pinA(void);
uint8_t rot_enc_read_pinB(void);

#endif /* __GPIO_H */
