#define BLYNK_TEMPLATE_ID "TMPLW5fieVsW"
#define BLYNK_DEVICE_NAME "Tonmoy"
#define BLYNK_AUTH_TOKEN "Pbmqi9py3IDbYGg1NaI1YQH4OFx4KMel"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "NAF Tech_WiFi";
char pass[] = "N@f Tech";
int value;

BlynkTimer timer;

BLYNK_WRITE(V0) {
  value = param.asInt();
  Blynk.virtualWrite(V1, value);
}

void myTimerEvent() {
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  digitalWrite(13, value);
}
