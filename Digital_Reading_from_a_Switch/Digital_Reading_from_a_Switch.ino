int x;
void setup() {
  pinMode(5, INPUT_PULLDOWN);
  Serial.begin(115200);
}
void loop() {
  x = digitalRead(5);
  Serial.println(x);
}
