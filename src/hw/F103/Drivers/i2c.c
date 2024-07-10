#include "i2c.h"
#include "f103.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_i2c.h"

static bool is_open[I2C_MAX_CH];
I2C_HandleTypeDef hi2c1;

bool I2CInit(void) {
  uint32_t i;

  for(i = 0;i < I2C_MAX_CH;i++) {
    is_open[i] = false;
  }

  return true;
}

bool I2COpen(uint8_t i2cCh, uint8_t own_addr) {
  bool ret = true;

  switch (i2cCh) {
    case _DEF_I2C1:
      hi2c1.Instance = I2C1;
      hi2c1.Init.ClockSpeed = 100000;
      hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
      hi2c1.Init.OwnAddress1 = own_addr;
      hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
      hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
      hi2c1.Init.OwnAddress2 = 0;
      hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
      hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
      if (HAL_I2C_Init(&hi2c1) != HAL_OK)
      {
        ret = false;
      } else {
        is_open[i2cCh] = true;
      }
      break;
  }

  return ret;
}

bool I2CTransmit(uint8_t i2cCh, uint16_t i2cAddr, uint8_t *p_data, uint16_t size) {
  HAL_StatusTypeDef status;
  I2C_HandleTypeDef *ch;
  switch (i2cCh) {
    case _DEF_I2C1:
      ch = &hi2c1;
      break;
  }
  
  if(!is_open[i2cCh]) {
    return false;
  }

  status = HAL_I2C_Master_Transmit(ch, i2cAddr, p_data, size, I2C_TIMEOUT);
  if(status != HAL_OK) {
    return false;
  }

  return true;
}

bool I2CReceive(uint8_t i2cCh, uint16_t i2cAddr, uint8_t *p_data, uint16_t size) {
  HAL_StatusTypeDef status;
  I2C_HandleTypeDef *ch;
  switch (i2cCh) {
    case _DEF_I2C1:
      ch = &hi2c1;
      break;
  }

  if(!is_open[i2cCh]) {
    return false;
  }

  status = HAL_I2C_Master_Receive(ch, i2cAddr, p_data, size, I2C_TIMEOUT);
  if(status != HAL_OK) {
    return false;
  }

  return true;
}

uint8_t I2CScan(uint8_t i2cCh) {
  uint8_t ret = 0;
  HAL_StatusTypeDef status;
  I2C_HandleTypeDef *ch;
  switch (i2cCh) {
    case _DEF_I2C1:
      ch = &hi2c1;
      break;
  }
  
  if(!is_open[i2cCh]) {
    return false;
  }


  for (uint8_t i = 0;i < 128;i++) {
    status = HAL_I2C_IsDeviceReady(ch, i << 1, 1, 10);
    if(status == HAL_OK) {
      ret = i;
      break;
    }
  }

  return ret;
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_7);

  /* USER CODE BEGIN I2C1_MspDeInit 1 */

  /* USER CODE END I2C1_MspDeInit 1 */
  }
}