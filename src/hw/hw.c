#include "hw.h"
#include "hw_def.h"

void HwInit(void) {
  TargetInit();

  GpioInit();
  UartInit();
  I2CInit();
}
