#include "LCD1602.h"
#include "def.h"
#include "i2c.h"

static LCD_BACKLIGHT _backlight = BACKLIGHT_OFF;

bool LCDInit(void) {
  Delay(20); // Wait power stable

  LCDSendCommand(0x30); // set 8 bit mode three times for stable
  Delay(5); // wait > 4.1ms
  LCDSendCommand(0x30);
  Delay(2); // wait > 1ms
  LCDSendCommand(0x30);
  Delay(2);
  LCDSendCommand(0x20); // set 4 bit mode
  Delay(2);

  LCDSendCommand(0x28); // set 4 bit & 2 line mode
  Delay(1);

  LCDSendCommand(0x08); // Display off
  Delay(1);

  LCDSendCommand(0x01); // Clear Display
  Delay(2);

  LCDSendCommand(0x06); // Entry mode (increment cursor)
  Delay(1);

  LCDSendCommand(0x0C); // Display on, Cursor off
  Delay(1);

  return true;
}

bool LCDSendCommand(uint8_t command) {
  uint8_t dividedCmd[4];
  uint8_t upperCmd, lowerCmd;
  bool ret;

  upperCmd = (command & 0xf0);
  lowerCmd = ((command << 4) & 0xf0);

  dividedCmd[0] = upperCmd | 0x04 | _backlight;
  dividedCmd[1] = upperCmd | 0x00 | _backlight;
  dividedCmd[2] = lowerCmd | 0x04 | _backlight;
  dividedCmd[3] = lowerCmd | 0x00 | _backlight;
  
  ret = I2CTransmit(_DEF_I2C1, LCD_I2C_SLAVE_ADDRESS, dividedCmd, 4);

  return ret;
}

bool LCDSendData(uint8_t data) {
  uint8_t dividedData[4];
  uint8_t upperData, lowerData;
  bool ret;

  upperData = (data & 0xf0);
  lowerData = ((data << 4) & 0xf0);

  dividedData[0] = upperData | 0x05 | _backlight;
  dividedData[1] = upperData | 0x01 | _backlight;
  dividedData[2] = lowerData | 0x05 | _backlight;
  dividedData[3] = lowerData | 0x01 | _backlight;
  
  ret = I2CTransmit(_DEF_I2C1, LCD_I2C_SLAVE_ADDRESS, dividedData, 4);

  return ret;
}

uint32_t LCDPrint(char *fmt, ...) {
  char buf[17];
  uint32_t len, ret = 0;

  va_list VA_LIST;
  va_start(VA_LIST, fmt);

  len = vsnprintf(buf, 16, fmt, VA_LIST);

  va_end(VA_LIST);
  
  if (len > 16) {
    len = 16; // Can't print over 16 chars
  }

  for (uint8_t i = 0;i < len;i++) {
    LCDSendData(buf[i]);
  }

  ret = len;

  return ret;
}

bool LCDClear(void) {
  bool ret;

  ret = LCDSendCommand(0x01);
  Delay(2);

  return ret;
}

bool LCDSetBackLight(LCD_BACKLIGHT backlight) {
  bool ret = true;

  _backlight = backlight;

  return ret;
}

bool LCDCursor(uint8_t row, uint8_t column) {
  bool ret = true;
  uint8_t rowOffsets[] = {0x00, 0x40};
  if (row > 1) {
    row = 0;
  }

  if (column > 27) {
    column = 0;
  }

  ret = LCDSendCommand(0x80 | (rowOffsets[row] + column));

  return ret;
}