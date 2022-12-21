int x;
bool state = 1;
void setup() {
  pinMode(32, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(5, INPUT_PULLUP);
  digitalWrite(32, 0);
  digitalWrite(25, 1);
  digitalWrite(14, 0);
  Serial.begin(9600);

}

void loop() {
  x = analogRead(33);
  Serial.println(x);
  if (x > 400 && state) digitalWrite(18, 1);
  else digitalWrite(18, 0);
  if (!digitalRead(5)) {
    while (!digitalRead(5));
    state = !state;
  }
}
