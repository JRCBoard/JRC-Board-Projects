void setup() {
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(18, OUTPUT);
  digitalWrite(14, LOW);
  
  
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);
  digitalWrite(18, LOW);
  delay(1000);
  digitalWrite(13, LOW);
  digitalWrite(18, HIGH);
  delay(1000);
}
