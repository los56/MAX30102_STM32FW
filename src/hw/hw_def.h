#ifndef __SRC_HW_HW_DEF_H__
#define __SRC_HW_HW_DEF_H__

#include "def.h"

#ifdef STM32F103xB
#include "f103_def.h"
#endif

void TargetInit(void);

void Delay(uint32_t ms);
uint32_t Millis(void);

#endif

