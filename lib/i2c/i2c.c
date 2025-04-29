#include "i2c.h"

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/twi.h>

void i2c_init(uint8_t bit_rate, uint8_t prescaler)
{
    switch (prescaler) {
    case 1:
        TWSR &= ~(_BV(TWPS0) | _BV(TWPS1));
        break;
    case 4:
        TWSR |= _BV(TWPS0);
        TWSR &= ~(_BV(TWPS1));
        break;
    case 16:
        TWSR &= ~(_BV(TWPS0));
        TWSR |= _BV(TWPS1);
        break;
    case 64:
        TWSR |= _BV(TWPS0) | _BV(TWPS1);
        break;
    }

    TWBR = bit_rate;
}

int8_t i2c_send(uint8_t address, uint8_t* data, uint32_t size)
{
    uint8_t i;

    /* Send START */

    TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);

    /* Wait for START being sent */

    loop_until_bit_is_set(TWCR, TWINT);

    /* Check that START is being sent correctly */

    if ((TWSR & 0xF8) != TW_START)
        return -1;

    /* Send the ADDRESS on the bus */

    TWDR = address;
    TWCR = _BV(TWINT) | _BV(TWEN);

    /* Wait for ADDRESS being sent */

    loop_until_bit_is_set(TWCR, TWINT);

    /* Check acknowledge of SLAVE */

    if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
        return -2;

    /* Send data */

    for (i = 0; i < size; i++) {
        /* Write data to the TWDR register */

        TWDR = data[i];

        /* Send data */

        TWCR = _BV(TWINT) | _BV(TWEN);

        /* Wait for data[i] being sent */

        loop_until_bit_is_set(TWCR, TWINT);

        /* Check data being correctly received */

        if ((TWSR & 0xF8) != TW_MT_DATA_ACK)
            return -3;
    }

    /* Send STOP */

    TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);

    return 0;
}
