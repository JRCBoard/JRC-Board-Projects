#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "YourAuthToken";
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  if(digitalRead(switch) == HIGH) {
    Serial.println("Send Notification to Blynk");
    Blynk.notify("Switch Pressed"); // This notification will be sent to Blynk App
  }
}
