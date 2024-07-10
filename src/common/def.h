#ifndef __SRC_COMMON_DEF_H__
#define __SRC_COMMON_DEF_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

// I2C
#define I2C_TIMEOUT       1000
#define _DEF_I2C1         0
#define _DEF_I2C2         1

// UART
#define UART_MAX_BUFFER   256
#define UART_TIMEOUT      1000

#define _DEF_UART1        0
#define _DEF_UART2        1
#define _DEF_UART3        2
#define _DEF_UART4        3
#define _DEF_UART_CDC     4

#endif
