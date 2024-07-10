#include "main.h"

#include "MAX30102.h"
#include "LCD1602.h"
#include "heart_rate.h"


void AppInit(void) {
  UartOpen(_DEF_UART1, 57600);
  I2COpen(_DEF_I2C1, 0x00);
}

void AppMain(void) {
  MAX30102_SAMPLE samples[32];
  uint32_t sampleSize = 0;

  uint32_t pre = Millis();
  uint32_t lastBeat = 0, deltaBeat, bpmIndex = 0;
  float bpm = 0.0f, avgBpm = 0, sumBpm = 0;

  float bpms[32];

  LCDInit();
  LCDSetBackLight(BACKLIGHT_ON);
  MAX30102_Init();

  for (uint32_t i = 0;i < 32;i++) {
    bpms[i] = 0.0f;
  }

  while(1) {
    if (Millis() - pre > 1000) {
      GpioToggle(PB12);

      LCDClear();
      LCDPrint("BPM: %.1f", bpm);
      LCDCursor(1, 0);
      LCDPrint("AVG: %.1f", avgBpm);

      pre = Millis();
    }

    sampleSize = MAX30102_FifoRead(samples, 32);
    if (sampleSize > 0) {
      if (samples[sampleSize - 1].ir >= 50000 && CheckForBeat(samples[sampleSize - 1].ir)) {
        deltaBeat = Millis() - lastBeat;

        bpm = 60 / (deltaBeat / 1000.0f);
        lastBeat = Millis();

        bpms[bpmIndex] = bpm;
        bpmIndex = (bpmIndex + 1) % 32;

        sumBpm = 0;
        for (uint32_t i = 0;i < 32;i++) {
          sumBpm += bpms[i];
        } 
        avgBpm = sumBpm / 32;
      }

      UartPrint(_DEF_UART1, "IR: %d, BPM: %.1f, AVG: %.1f\n", samples[sampleSize - 1].ir, bpm, avgBpm);
    }
    Delay(10);
  }
}
