#ifndef __SRC_COMMON_TYPES_CIRCULAR_BUFFER_H__
#define __SRC_COMMON_TYPES_CIRCULAR_BUFFER_H__

#include "def.h"

typedef struct {
  uint32_t head;
  uint32_t tail;
  uint32_t len;

  uint8_t *p_arr;
} cbuffer_t;

bool cBufferCreate(cbuffer_t *cbuffer, uint8_t *p_arr, uint32_t len);
bool cBufferEnqueue(cbuffer_t *cbuffer, uint8_t data);
bool cBufferDequeue(cbuffer_t *cbuffer, uint8_t *p_data);
uint32_t cBufferAvailable(cbuffer_t *cbuffer);
bool cBufferFlush(cbuffer_t *cbuffer);

#endif
