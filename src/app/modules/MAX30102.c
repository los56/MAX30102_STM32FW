#include "MAX30102.h"
#include "MAX30102_def.h"

void MAX30102_Init(void) {
  MAX30102_RegWrite(MAX30102_REG_FIFO_CONFIG, 0x50);
  MAX30102_RegWrite(MAX30102_REG_SPO2_CONFIG, 0x4F);

  MAX30102_LedPASet(LED_RED, MAX30102_DEFAULT_LED_RED_PA);
  MAX30102_LedPASet(LED_IR, MAX30102_DEFAULT_LED_IR_PA);

  MAX30102_ModeSet(MAX30102_DEFAULT_MODE);

  MAX30102_FifoFlush();
}

void MAX30102_IntrEnable(uint8_t intr1, uint8_t intr2) {  
  
}

bool MAX30102_ModeSet(MAX30102_MODE mode) {
  bool ret = true;
  
  if (mode == UNKNOWN) {
    ret = false;
  } else {
    ret = MAX30102_RegUpdate(MAX30102_REG_MODE_CONFIG, mode, MAX30102_MODE_MASK_MODE);
  }

  return ret;
}

MAX30102_MODE MAX30102_ModeGet(void) {
  MAX30102_MODE mode = UNKNOWN;
  uint8_t buf = 0;
  bool status;

  status = MAX30102_RegRead(MAX30102_REG_MODE_CONFIG, &buf, 1);

  if (!status) {
    return mode;
  }

  buf &= MAX30102_MODE_MASK_MODE;
  mode = (MAX30102_MODE) buf;

  return mode;  
}

bool MAX30102_RegRead(uint8_t reg_addr, uint8_t *p_data, uint32_t length) {
  bool ret = true, status;
  uint8_t i2cAddr;
  uint8_t *buf;

  if (length == 0) {
    ret = false;
    return ret;
  }

  buf = malloc(sizeof(uint8_t) * length);

  i2cAddr = (MAX30102_I2C_ADDR | MAX30102_I2C_FLAG_WRITE);
  buf[0] = reg_addr;
  status = I2CTransmit(_DEF_I2C1, i2cAddr, &buf[0], 1);

  if (!status) {
    ret = false;
    return ret;
  }

  i2cAddr = (MAX30102_I2C_ADDR | MAX30102_I2C_FLAG_READ);
  status = I2CReceive(_DEF_I2C1, i2cAddr, buf, length);
  
  if (!status) {
    ret = false;
  } else {
    memcpy(p_data, buf, length);
  }

  free(buf);
  
  return ret;
}

bool MAX30102_RegWrite(uint8_t reg_addr, uint8_t data) {
  bool ret = true;
  uint8_t i2cAddr = (MAX30102_I2C_ADDR | MAX30102_I2C_FLAG_WRITE);
  uint8_t buf[2] = { reg_addr, data };
  
  ret = I2CTransmit(_DEF_I2C1, i2cAddr, buf, 2);

  return ret;
}

bool MAX30102_RegUpdate(uint8_t reg_addr, uint8_t data, uint8_t mask) {
  bool ret = true, status;
  uint8_t buf = 0;
  uint8_t notChangeMask = ~(mask);

  status = MAX30102_RegRead(reg_addr, &buf, 1);
  if (!status) {
    ret = false;
    return ret;
  }
  
  buf &= notChangeMask;
  buf |= (data & mask);

  status = MAX30102_RegWrite(reg_addr, buf);
  if (!status) {
    ret = false;
  }

  return ret;
}

uint32_t MAX30102_FifoRead(MAX30102_SAMPLE *p_data, uint32_t length) {
  uint8_t readPtr, writePtr;
  uint8_t buf[6];
  uint32_t bytesEachSample, ret = 0;
  int32_t dataCount, i;
  bool status;

  MAX30102_MODE mode;

  if (length > MAX30102_FIFO_MAX_UNREAD_DATA) {
    length = MAX30102_FIFO_MAX_UNREAD_DATA;
  }

  status = MAX30102_RegRead(MAX30102_REG_FIFO_WR_PTR, &writePtr, 1);
  if (!status) {
    return ret;
  }
  
  status = MAX30102_RegRead(MAX30102_REG_FIFO_RD_PTR, &readPtr, 1);
  if (!status) {
    return ret;
  }

  dataCount = ((int32_t)writePtr - (int32_t)readPtr);
  if (dataCount < 0) {
    dataCount += 32;
  }

  mode = MAX30102_ModeGet();

  if (dataCount > (int32_t)length) {
    dataCount = length;
  }

  if(mode == SPO2) {
    bytesEachSample = 6;
  } else {
    bytesEachSample = 3;
  }

  for (i = 0;i < dataCount;i++) {
    status = MAX30102_RegRead(MAX30102_REG_FIFO_DATA, buf, bytesEachSample);
    if (!status) {
      break;
    }

    p_data[i].red  = ((uint32_t)(buf[0] & 0x03) << 16);
    p_data[i].red |= ((uint32_t)buf[1] << 8);
    p_data[i].red |= ((uint32_t)buf[2] << 0);

    if (mode == SPO2) {
      p_data[i].ir  = ((uint32_t)(buf[3] & 0x03) << 16);
      p_data[i].ir |= ((uint32_t)buf[4] << 8);
      p_data[i].ir |= ((uint32_t)buf[5] << 0);
    }
  }

  ret = (uint32_t)i;

  return ret;
}

void MAX30102_FifoFlush(void) {
  MAX30102_RegWrite(MAX30102_REG_FIFO_WR_PTR, 0);
  MAX30102_RegWrite(MAX30102_REG_OVR_COUNTER, 0);
  MAX30102_RegWrite(MAX30102_REG_FIFO_RD_PTR, 0);
}

bool MAX30102_LedPASet(MAX30102_LED led, float amp) {
  bool ret = false;
  uint8_t targetAddr;
  uint8_t convertedAmp = (uint8_t)(amp / 0.2f);

  if (led == LED_RED) {
    targetAddr = MAX30102_REG_LED1_PA;
  } else if (led == LED_IR) {
    targetAddr = MAX30102_REG_LED2_PA;
  } else {
    return ret;
  }

  ret = MAX30102_RegWrite(targetAddr, convertedAmp);

  return ret;
}

float MAX30102_LedPAGet(MAX30102_LED led) {
  float ret = 0;
  uint8_t targetAddr, buf = 0;
  bool status;

  if (led == LED_RED) {
    targetAddr = MAX30102_REG_LED1_PA;
  } else if (led == LED_IR) {
    targetAddr = MAX30102_REG_LED2_PA;
  } else {
    return ret;
  }

  status = MAX30102_RegRead(targetAddr, &buf, 1);
  if (status) {
    ret = buf * 0.2f;
  }

  return ret;
}
