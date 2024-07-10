#ifndef __SRC_COMMON_DRIVERS_UART_H__
#define __SRC_COMMON_DRIVERS_UART_H__

#include "hw_def.h"

#define UART_MAX_CH   HW_UART_MAX_CH

bool      UartInit(void);
bool      UartOpen(uint8_t ch, uint32_t baud);
uint32_t  UartAvailable(uint8_t ch);
uint8_t   UartRead(uint8_t ch);
uint32_t  UartWrite(uint8_t ch, uint8_t *p_data, uint32_t size);
uint32_t  UartPrint(uint8_t ch, char *fmt, ...);

#endif
