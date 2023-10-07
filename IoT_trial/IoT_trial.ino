#include "ndcs_esp32.h"
char* wifi_ssid = "JRC Board";     // put your wifi ssid in between the quotes
char* wifi_password = "robotics";  // put your wifi password in between the quotes
char* email = "frontech.iot@gmail.com";
char* password = "T3chn0l0gy";  // put your account's password in between the quotes
char* device_id = "OzS5VLBl8jZduiLbCCRt";

NDCS Ndcs;

void setup() {
  Serial.begin(115200);
  Ndcs.begin(wifi_ssid, wifi_password, email, password, device_id);
}

void loop() {
}
