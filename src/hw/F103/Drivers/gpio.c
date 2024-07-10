#include "gpio.h"
#include "f103.h"

static GPIO_TypeDef* getGPIOx(uint16_t pin);

bool GpioInit(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  return true;
}

bool GpioHigh(uint16_t pin) {
  uint16_t targetPin = 0x01 << (pin & 0x0F);
  GPIO_TypeDef *gpiox = getGPIOx(pin);

  HAL_GPIO_WritePin(gpiox, targetPin, GPIO_PIN_SET);

  return true;
}

bool GpioLow(uint16_t pin) {
  uint16_t targetPin = 0x01 << (pin & 0x0F);
  GPIO_TypeDef *gpiox = getGPIOx(pin);

  HAL_GPIO_WritePin(gpiox, targetPin, GPIO_PIN_RESET);

  return true;
}

bool GpioToggle(uint16_t pin) {
  uint16_t targetPin = 0x01 << (pin & 0x0F);
  GPIO_TypeDef *gpiox = getGPIOx(pin);

  HAL_GPIO_TogglePin(gpiox, targetPin);

  return true;
}

GPIO_TypeDef* getGPIOx(uint16_t pin) {
  uint16_t xbit = (pin >> 4);
  GPIO_TypeDef* ret = NULL;

  switch(xbit) {
    case GPIOA_MASK:
      ret = GPIOA;
      break;
    case GPIOB_MASK:
      ret = GPIOB;
      break;
    case GPIOC_MASK:
      ret = GPIOC;
      break;
    case GPIOD_MASK:
      ret = GPIOD;
      break;
  }

  return ret;
}
