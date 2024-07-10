#ifndef __SRC_HW_F103_DEF_H__
#define __SRC_HW_F103_DEF_H__

#include "stm32f103xb.h"

// GPIO PIN INDEX
#define PA0     0x10
#define PA1     0x11
#define PA2     0x12
#define PA3     0x13
#define PA4     0x14
#define PA5     0x15
#define PA6     0x16
#define PA7     0x17
#define PA8     0x18
#define PA9     0x19
#define PA10    0x1A
#define PA11    0x1B
#define PA12    0x1C
#define PA13    0x1D
#define PA14    0x1E
#define PA15    0x1F

#define PB0     0x20
#define PB1     0x21
#define PB2     0x22
#define PB3     0x23
#define PB4     0x24
#define PB5     0x25
#define PB6     0x26
#define PB7     0x27
#define PB8     0x28
#define PB9     0x29
#define PB10    0x2A
#define PB11    0x2B
#define PB12    0x2C
#define PB13    0x2D
#define PB14    0x2E
#define PB15    0x2F

#define PC0     0x40
#define PC1     0x41
#define PC2     0x42
#define PC3     0x43
#define PC4     0x44
#define PC5     0x45
#define PC6     0x46
#define PC7     0x47
#define PC8     0x48
#define PC9     0x49
#define PC10    0x4A
#define PC11    0x4B
#define PC12    0x4C
#define PC13    0x4D
#define PC14    0x4E
#define PC15    0x4F

#define PD0     0x80
#define PD1     0x81

#define GPIOA_MASK  0x01
#define GPIOB_MASK  0x02
#define GPIOC_MASK  0x04
#define GPIOD_MASK  0x08
// End GPIO PIN INDEX

// I2C Define
#define HW_I2C_MAX_CH   1

// UART Define
#define HW_UART_MAX_CH  1

#endif
