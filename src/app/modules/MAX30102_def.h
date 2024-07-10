#ifndef __SRC_APP_MODULES_MAX30102_DEF_H__
#define __SRC_APP_MODULES_MAX30102_DEF_H__

#include <stdint.h>

// Module Infomation
#define MAX30102_I2C_ADDR            0xAE
#define MAX30102_I2C_FLAG_WRITE      0x00
#define MAX30102_I2C_FLAG_READ       0x01

// Register Map
#define MAX30102_REG_INTR1_STATUS    0x00
#define MAX30102_REG_INTR2_STATUS    0x01
#define MAX30102_REG_INTR1_ENABLE    0x02
#define MAX30102_REG_INTR2_ENABLE    0x03

#define MAX30102_REG_FIFO_WR_PTR     0x04
#define MAX30102_REG_OVR_COUNTER     0x05
#define MAX30102_REG_FIFO_RD_PTR     0x06
#define MAX30102_REG_FIFO_DATA       0x07
#define MAX30102_REG_FIFO_CONFIG     0x08

#define MAX30102_REG_MODE_CONFIG     0x09
#define MAX30102_REG_SPO2_CONFIG     0x0A

#define MAX30102_REG_LED1_PA         0x0C
#define MAX30102_REG_LED2_PA         0x0D

#define MAX30102_REG_MULTILED_MC1    0x11
#define MAX30102_REG_MULTILED_MC2    0x12

#define MAX30102_REG_DIETEMP_INT     0x1F
#define MAX30102_REG_DIETEMP_FRAC    0x20
#define MAX30102_REG_DIETEMP_CONFIG  0x21

#define MAX30102_REG_REV_ID          0xFE
#define MAX30102_REG_PART_ID         0xFF

// Interrupt Status Flags
#define MAX30102_INTR1_FLAG_A_FULL         (0x01 << 7) // FIFO almost full (depend on FIFO_A_FULL register)
#define MAX30102_INTR1_FLAG_PPG_RDY        (0x01 << 6) // New FIFO data ready
#define MAX30102_INTR1_FLAG_ACL_OVF        (0x01 << 5) // ?
#define MAX30102_INTR1_FLAG_PWR_RDY        (0x01 << 0) // Power-Up or After a brownout condition 
#define MAX30102_INTR2_FLAG_DIE_TMP_RDY    (0x01 << 1) // Internal die temperature conversion finished

// FIFO Config Masks & Types
#define MAX30102_FIFO_MASK_SMP_AVE         (0x07 << 5) // Sample averaging
#define MAX30102_FIFO_MASK_ROLLOVER        (0x01 << 4) // (1): FIFO is circular, (0): FIFO is not updated untill FIFO_DATA read or WR/RD pointer are changed
#define MAX30102_FIFO_MASK_A_FULL          (0x0F << 0) // Empty data samples in FIFO when interrupt is issued (0x0 ~ 0xF)

typedef enum {
  SAM_AVE1  = (0x00 << 5),
  SAM_AVE2  = (0x01 << 5),
  SAM_AVE4  = (0x02 << 5),
  SAM_AVE8  = (0x03 << 5),
  SAM_AVE16 = (0x04 << 5),
  SAM_AVE32 = (0x05 << 5),
} MAX30102_FIFO_SMP_AVE;

typedef struct {
  uint32_t red;
  uint32_t ir;
} MAX30102_SAMPLE;

#define MAX30102_FIFO_MAX_UNREAD_DATA      32

// Mode Config Masks & Types
#define MAX30102_MODE_MASK_SHDN            (0x01 << 7) // Power-save mode
#define MAX30102_MODE_MASK_RESET           (0x01 << 6) // Reset (all register clear)
#define MAX30102_MODE_MASK_MODE            (0x07 << 0) // Mode

typedef enum {
  HEART_RATE = 0x2,
  SPO2       = 0x3,
  MULTI_LED  = 0x7, 
  UNKNOWN    = 0xF
} MAX30102_MODE;

// SpO₂ Config Masks & Types
#define MAX30102_SPO2_MASK_ADC_RGE         (0x03 << 5) // ADC range control
#define MAX30102_SPO2_MASK_SR              (0x04 << 5) // Sample rate
#define MAX30102_SPO2_MASK_LED_PW          (0x03 << 0) // LED pulse width

typedef enum {
  SPS_50 = 0x0,
  SPS_100,
  SPS_200,
  SPS_400,
  SPS_800,
  SPS_1000,
  SPS_1600,
  SPS_3200
} MAX30102_SPO2_SR;

typedef enum {
  PW_69 = 0x0,
  PW_118,
  PW_215,
  PW_411
} MAX30102_SPO2_LED_PW;

// Multi-LED Mode Control Masks
#define MAX30102_MULTILED_MC1_MASK_SLOT1       (0x07 << 0)
#define MAX30102_MULTILED_MC1_MASK_SLOT2       (0x07 << 4)
#define MAX30102_MULTILED_MC2_MASK_SLOT3       (0x07 << 0)
#define MAX30102_MULTILED_MC2_MASK_SLOT4       (0x07 << 4)

// Temperature Data Masks
#define MAX30102_DIETEMP_FRAC_MASK_FRAC        (0x0F << 0)
#define MAX30102_DIETEMP_MASK_ENABLE           (0x01 << 0)

typedef enum {
  LED_NONE = 0x0,
  LED_RED,
  LED_IR
} MAX30102_LED;


#endif
