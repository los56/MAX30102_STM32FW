#ifndef __SRC_APP_MODULES_MAX30102_H__
#define __SRC_APP_MODULES_MAX30102_H__

#include "main.h"

#include "MAX30102_def.h"

void      MAX30102_Init(void);
void      MAX30102_IntrEnable(uint8_t intr1, uint8_t intr2);

bool      MAX30102_ModeSet(MAX30102_MODE mode);
MAX30102_MODE MAX30102_ModeGet(void);

bool      MAX30102_RegRead(uint8_t reg_addr, uint8_t *p_data, uint32_t length);
bool      MAX30102_RegWrite(uint8_t reg_addr, uint8_t data);
bool      MAX30102_RegUpdate(uint8_t reg_addr, uint8_t data, uint8_t mask);

uint32_t  MAX30102_FifoRead(MAX30102_SAMPLE *p_data, uint32_t length);
void      MAX30102_FifoFlush(void);

bool      MAX30102_LedPASet(MAX30102_LED led, float amp);
float     MAX30102_LedPAGet(MAX30102_LED led);



// Deault Setting
#define MAX30102_DEFAULT_MODE             ((MAX30102_MODE) SPO2)
#define MAX30102_DEFAULT_LED_RED_PA       2.0f
#define MAX30102_DEFAULT_LED_IR_PA        6.4f

#define MAX30102_DEFAULT_FIFO_READ_COUNT  32


#endif
