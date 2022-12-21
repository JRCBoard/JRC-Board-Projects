#define BLYNK_TEMPLATE_ID "TMPLW5fieVsW"
#define BLYNK_DEVICE_NAME "Tonmoy"
#define BLYNK_AUTH_TOKEN "Pbmqi9py3IDbYGg1NaI1YQH4OFx4KMel"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "The Tiny Bear";
char pass[] = "bolajabena";

bool value[15];
bool state[15];
int button[] = {15, 2, 4};
int output[] = {5, 14, 13};
int led[] = {23, 19, 18};
int count = 3;
const int threshold = 20;
BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < count; i++) pinMode(output[i], OUTPUT);
  for (int i = 0; i < count; i++) pinMode(led[i], OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run();
  touchUpdate();
  statUpdate();
  for (int i = 0; i < count; i++) {
    digitalWrite(output[i], value[i]);
    digitalWrite(led[i], value[i]);
  }
}
