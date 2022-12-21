void setup() {
  pinMode(26, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  Serial.println(analogRead(25));
  if (analogRead(25) > 800) {
    digitalWrite(26, 1); digitalWrite(13, 1); delay(250);
    digitalWrite(26, 0); digitalWrite(13, 0); delay(250);
  }
  else {
    digitalWrite(26, 0);
    digitalWrite(13, 0);
  }

}
