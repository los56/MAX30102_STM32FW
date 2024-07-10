#ifndef __SRC_APP_MODULES_LCD1602_H__
#define __SRC_APP_MODULES_LCD1602_H__

#include "main.h"

#define LCD_I2C_SLAVE_ADDRESS   0x4E

typedef enum {
  BACKLIGHT_OFF = 0x0,
  BACKLIGHT_ON = 0x8,
} LCD_BACKLIGHT;

bool LCDInit(void);

bool LCDSendCommand(uint8_t command);
bool LCDSendData(uint8_t data);

uint32_t LCDPrint(char *fmt, ...);
bool LCDClear(void);
bool LCDSetBackLight(LCD_BACKLIGHT backlight);

bool LCDCursor(uint8_t row, uint8_t column);

#endif
