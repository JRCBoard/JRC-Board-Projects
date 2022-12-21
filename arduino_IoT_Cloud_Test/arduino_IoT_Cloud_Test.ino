#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
const char SSID[] = "NAF Tech_WiFi";    // Network SSID (name)
const char PASS[] = "N@f Tech";    // Network password (use for WPA, or use as key for WEP)
void onLedChange();
bool led;

void initProperties() {
  ArduinoCloud.setBoardId("09a84c20-b2be-415a-946e-d1b08c08ca25");
  ArduinoCloud.setSecretDeviceKey("2ZXWQXC9GYGXBGGHXBZU");
  ArduinoCloud.addProperty(led, READWRITE, ON_CHANGE, onLedChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void setup() {
  Serial.begin(115200);
  delay(1500);
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  pinMode(13, OUTPUT);
  pinMode(14, INPUT_PULLUP);
}

void loop() {
  ArduinoCloud.update();
  if (!digitalRead(14)) {
    led = 0;
    digitalWrite(13, led);
  }

}

void onLedChange()  {
  digitalWrite(13, led);
}
