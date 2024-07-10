#include "uart.h"
#include "f103.h"

static bool is_open[UART_MAX_CH];

UART_HandleTypeDef huart1;

bool UartInit(void) {
  bool ret = true;
  uint32_t i;

  for (i = 0; i < UART_MAX_CH; i++) {
    is_open[i] = false;
  }

  return ret;
}

bool UartOpen(uint8_t ch, uint32_t baud) {
  bool ret = false;

  switch (ch) {
  case _DEF_UART1:
    huart1.Instance = USART1;
    huart1.Init.BaudRate = baud;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_DeInit(&huart1);

    if (HAL_UART_Init(&huart1) != HAL_OK) {
      ret = false;
    } else {
      ret = true;
      is_open[ch] = true;
    }
    break;
  }

  return ret;
}

uint32_t UartAvailable(uint8_t ch) {
  return 0;
}

uint8_t UartRead(uint8_t ch) {
  return 0;
}

uint32_t UartWrite(uint8_t ch, uint8_t *p_data, uint32_t size) {
  HAL_StatusTypeDef status;
  uint32_t ret = 0;

  switch(ch) {
    case _DEF_UART1:
      status = HAL_UART_Transmit(&huart1, p_data, size, UART_TIMEOUT);
      if(status == HAL_OK) {
        ret = size;
      }
  }

  return ret;
}

uint32_t UartPrint(uint8_t ch, char *fmt, ...) {
  char buf[256];
  uint32_t len, ret = 0;

  va_list VA_LIST;
  va_start(VA_LIST, fmt);

  len = vsnprintf(buf, 256, fmt, VA_LIST);

  va_end(VA_LIST);

  switch(ch) {
    case _DEF_UART1:
        ret = UartWrite(ch, (uint8_t *)buf, len);
        break;
  }

  return ret;
}


// CubeMX Generated Code
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
}