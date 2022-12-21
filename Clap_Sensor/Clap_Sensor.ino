void setup() {
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(4, INPUT);
  digitalWrite(0, 1);
  digitalWrite(2, 0);

}

void loop() {
  if (digitalRead(4)) {
    digitalWrite(18, !digitalRead(18)); delay(1000);
  }
}
