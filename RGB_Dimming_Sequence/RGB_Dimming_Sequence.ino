int red = 15, green = 17, blue=4;

void setup() {
  ledcSetup(0, 1000, 8);
  ledcSetup(1, 1000, 8);
  ledcSetup(2, 1000, 8);
  ledcAttachPin(red, 0);
  ledcAttachPin(green, 1);
  ledcAttachPin(blue, 2);
  pinMode(16, OUTPUT);
  digitalWrite(16, 0);
}
void loop() {
  for (int i = 0; i <= 255; i++) {
    ledcWrite(0, i); delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    ledcWrite(2, i); delay(10);
  }
  for (int i = 0; i <= 255; i++) {
    ledcWrite(1, i); delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    ledcWrite(0, i); delay(10);
  }
  for (int i = 0; i <= 255; i++) {
    ledcWrite(2, i); delay(10);
  }
  for (int i = 255; i >= 0; i--) {
    ledcWrite(1, i); delay(10);
  }
}
