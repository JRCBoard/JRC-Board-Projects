bool alarm = 0;
int sensor = 26, buzzer = 23, button = 14;

void IRAM_ATTR sense() {
  alarm = 1;
}
void IRAM_ATTR push() {
  alarm = 0;
}

void setup() {
  Serial.begin(115200);
  pinMode(button, INPUT_PULLUP);
  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(5, OUTPUT); pinMode(32, OUTPUT);
  digitalWrite(5, 0); digitalWrite(32, 1);
  attachInterrupt(sensor, sense, CHANGE);
  attachInterrupt(button, push, FALLING);
}

void loop() {
  if (alarm) {
    digitalWrite(buzzer, 1); delay(250);
    digitalWrite(buzzer, 0); delay(250);
  }
  else digitalWrite(buzzer, 0);
}
