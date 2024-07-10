#include "circular_buffer.h"

bool cBufferCreate(cbuffer_t *cbuffer, uint8_t *p_arr, uint32_t len) {
  bool ret = true;

  cbuffer->head = 0;
  cbuffer->tail = 0;
  cbuffer->len = len;
  cbuffer->p_arr = p_arr;

  return ret;
}

bool cBufferEnqueue(cbuffer_t *cbuffer, uint8_t data) {
  uint32_t desireHead;
  if (cbuffer == NULL || cbuffer->p_arr == NULL) {
    return false;
  }

  desireHead = (cbuffer->head + 1) % cbuffer->len;
  cbuffer->p_arr[cbuffer->head] = data;

  if (desireHead == cbuffer->tail) {
    // Overwrite
    cbuffer->tail = (cbuffer->tail + 1) % cbuffer->len;
  }
  cbuffer->head = (cbuffer->head + 1) % cbuffer->len;

  return true;
}

bool cBufferDequeue(cbuffer_t *cbuffer, uint8_t *p_data) {
  if (cbuffer == NULL || cbuffer->p_arr == NULL) {
    return false;
  }

  // Empty
  if (cbuffer->head == cbuffer->tail) {
     return false;
  }

  *p_data = cbuffer->p_arr[cbuffer->tail];
  cbuffer->tail = (cbuffer->tail + 1) % cbuffer->len;

  return true;
}

uint32_t cBufferAvailable(cbuffer_t *cbuffer) {
  uint32_t ret;
  if(cbuffer == NULL || cbuffer->p_arr == NULL) {
    return 0;
  }
  
  ret = (cbuffer->len + cbuffer->head - cbuffer->tail) % cbuffer->len;

  return ret;
}

bool cBufferFlush(cbuffer_t *cbuffer) {
  if(cbuffer == NULL || cbuffer->p_arr == NULL) {
    return false;
  }

  cbuffer->head = 0;
  cbuffer->tail = 0;

  return true;
}
