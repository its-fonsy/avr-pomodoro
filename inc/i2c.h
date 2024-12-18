#ifndef __I2C_H
#define __I2C_H

#include <stdint.h>

void i2c_init(uint8_t bit_rate, uint8_t prescaler);
uint8_t i2c_send(uint8_t address, uint8_t *data, uint32_t size);

#endif /* __I2C_H */
