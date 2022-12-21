void setup() {
  ledcSetup(0, 1000, 8); ledcAttachPin(5, 0);
  pinMode(19, OUTPUT); pinMode(23, OUTPUT);
  pinMode(0, OUTPUT); pinMode(16, OUTPUT);
  digitalWrite(0, 1); digitalWrite(16, 0);
}
void loop() {
  int p = analogRead(4);
  p = map(p, 0, 4095, 0, 511);
  if (p < 200) {
    digitalWrite(19, 1); digitalWrite(23, 0);
    ledcWrite(0, 256 - p);
  }
  else if (p > 300) {
    digitalWrite(19, 0); digitalWrite(23, 1);
    ledcWrite(0, p - 256);
  }
  else {
    digitalWrite(19, 0); digitalWrite(23, 0);
  }
}
