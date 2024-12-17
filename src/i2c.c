#include <util/twi.h>
#include <stdint.h>

#include "hal.h"
#include "main.h"
#include "i2c.h"

void i2c_init(uint8_t bit_rate, uint8_t prescaler)
{
  switch(prescaler)
  {
    case 1:
      reset_pin(TWSR, TWPS0);
      reset_pin(TWSR, TWPS1);
      break;
    case 4:
      set_pin(TWSR, TWPS0);
      reset_pin(TWSR, TWPS1);
      break;
    case 16:
      reset_pin(TWSR, TWPS0);
      set_pin(TWSR, TWPS1);
      break;
    case 64:
      set_pin(TWSR, TWPS0);
      set_pin(TWSR, TWPS1);
      break;
  }

  TWBR = bit_rate;
}

uint8_t i2c_send(uint8_t address, uint8_t *data, uint8_t size)
{
  uint8_t i;

  /* Send START */

  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

  /* Wait for START being sent */

  while (!(TWCR & (1 << TWINT)))
      ;

  /* Check that START is being sent correctly */

  if ((TWSR & 0xF8) != TW_START)
    return -1;

  /* Send the ADDRESS on the bus */

  TWDR = address;
  TWCR = (1 << TWINT) | (1 << TWEN);

  /* Wait for ADDRESS being sent */

  while (!(TWCR & (1 << TWINT)))
      ;

  /* Check acknowledge of SLAVE */

  if ((TWSR & 0xF8) != TW_MT_SLA_ACK)
    return -2;

  /* Send data */

  for(i = 0; i < size; i++)
  {
    /* Write data to the TWDR register */

    TWDR = data[i];

    /* Send data */

    TWCR = (1 << TWINT) | (1 << TWEN);

    /* Wait for data[i] being sent */

    while (!(TWCR & (1 << TWINT)))
      ;

    /* Check data being correctly received */

    if ((TWSR & 0xF8) != TW_MT_DATA_ACK)
      return -3;
  }

  /* Send STOP */

  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);

  return 0;
}

