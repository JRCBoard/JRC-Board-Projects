float x;

void setup() {
  pinMode(18, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  x = analogRead(26) * 0.8;
  x = x / 10;
  if (x >= 40) {
    digitalWrite(18, 1); delay(250);
    digitalWrite(18, 0); delay(250);
  }
  else digitalWrite(18, 0);
  Serial.print(x);
  Serial.println(" ºC");
}
