#define BLYNK_TEMPLATE_ID "TMPLEDYV3X0k"
#define BLYNK_DEVICE_NAME "LED"
#define BLYNK_FIRMWARE_VERSION "0.1.3"
#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG
#define APP_DEBUG
#include "BlynkEdgent.h"

bool value[] = {0, 1, 1};
bool state[] = {0, 1, 1};
int button[] = {15, 2, 4};
int led[] = {5, 13, 14};
int count = 3;
const int threshold = 60;
BlynkTimer timer;

void setup()
{
  Serial.begin(115200);
  for (int i = 0; i < count; i++) pinMode(led[i], OUTPUT);
  BlynkEdgent.begin();
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
  touchUpdate();
  statUpdate();
  for (int i = 0; i < count; i++) {
    (i == 0) ? digitalWrite(led[i], value[i]) : digitalWrite(led[i], !value[i]);
  }
}
