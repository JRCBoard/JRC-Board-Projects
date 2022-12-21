#define BLYNK_TEMPLATE_ID "TMPLEDYV3X0k"
#define BLYNK_DEVICE_NAME "LED"
#define BLYNK_AUTH_TOKEN "a5spuhvHAu6l_L4OGd_I6M3JVJo_6M1q"
#define BLYNK_FIRMWARE_VERSION        "0.1.2"
#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG
#define APP_DEBUG
#include "BlynkEdgent.h"

bool value[15];
bool state[15];
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
  for (int i = 0; i < count; i++) digitalWrite(led[i], value[i]);
}
