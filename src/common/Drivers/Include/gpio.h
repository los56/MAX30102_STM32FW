#ifndef __SRC_COMMON_DRIVERS_GPIO_H__
#define __SRC_COMMON_DRIVERS_GPIO_H__

#include "hw_def.h"

bool GpioInit(void);
bool GpioHigh(uint16_t pin);
bool GpioLow(uint16_t pin);
bool GpioToggle(uint16_t pin);

#endif
