#include "lpc17xx_i2c.h"

void init_i2c_eeprom(LPC_I2C_TypeDef *,FunctionalState,uint32_t);
void i2c_eeprom_write(LPC_I2C_TypeDef*,uint16_t,uint8_t*, int);
void i2c_eeprom_read(LPC_I2C_TypeDef*,uint16_t,uint8_t*, int);
