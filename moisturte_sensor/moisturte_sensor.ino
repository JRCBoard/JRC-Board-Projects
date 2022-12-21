int led_pin = 18;
int sensor_pin = 16;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(sensor_pin, INPUT);
  pinMode(4, OUTPUT); pinMode(17, OUTPUT);
  digitalWrite(4, 1); digitalWrite(17, 0);
  Serial.begin(9600);
}

void loop() {
  Serial.println(String(digitalRead(sensor_pin)) + " " + String(analogRead(15)));
  digitalWrite(led_pin, !digitalRead(sensor_pin));
}
