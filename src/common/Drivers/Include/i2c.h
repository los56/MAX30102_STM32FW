#ifndef __SRC_COMMON_DRIVERS_I2C_H__
#define __SRC_COMMON_DRIVERS_I2C_H__

#include "hw_def.h"

#define I2C_MAX_CH    HW_I2C_MAX_CH

bool    I2CInit(void);
bool    I2COpen(uint8_t i2cCh, uint8_t own_addr);
bool    I2CTransmit(uint8_t i2cCh, uint16_t i2cAddr, uint8_t *p_data, uint16_t size);
bool    I2CReceive(uint8_t i2cCh, uint16_t i2cAddr, uint8_t *p_data, uint16_t size);
uint8_t I2CScan(uint8_t i2cCh);

#endif
