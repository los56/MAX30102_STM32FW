#ifndef __SRC_APP_ALGORITHM_HEART_RATE_H__
#define __SRC_APP_ALGORITHM_HEART_RATE_H__

#include <stdbool.h>
#include <stdint.h>

bool CheckForBeat(int32_t sample);
int16_t AverageDCEstimator(int32_t *p, uint16_t x);
int16_t LowPassFIRFilter(int16_t din);

#endif
