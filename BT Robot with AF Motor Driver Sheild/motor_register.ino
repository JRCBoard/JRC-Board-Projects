void motor1(bool a, byte b) {
  (a == 1) ? data = data | B00000100 : data = data & B11111011;
  (a == 1) ? data = data & B11110111 : data = data | B00001000;
  ledcWrite(12, b);
  motor_update(data);
}
void motor2(bool a, byte b) {
  (a == 1) ? data = data | B00000010 : data = data & B11111101;
  (a == 1) ? data = data & B11101111 : data = data | B00010000;
  ledcWrite(13, b);
  motor_update(data);
}
void motor3(bool a, byte b) {
  (a == 1) ? data = data | B00100000 : data = data & B11011111;
  (a == 1) ? data = data & B01111111 : data = data | B10000000;
  ledcWrite(14, b);
  motor_update(data);
}
void motor4(bool a, byte b) {
  (a == 1) ? data = data | B00000001 : data = data & B11111110;
  (a == 1) ? data = data & B10111111 : data = data | B01000000;
  ledcWrite(15, b);
  motor_update(data);
}

void motor1_stop() {
  data = data & B11110011;
  ledcWrite(12, 0);
  motor_update(data);
}
void motor2_stop() {
  data = data & B11101101;
  ledcWrite(13, 0);
  motor_update(data);
}
void motor3_stop() {
  data = data & B10111110;
  ledcWrite(14, 0);
  motor_update(data);
}
void motor4_stop() {
  data = data & B01011111;
  ledcWrite(15, 0);
  motor_update(data);
}

void motor_stop() {
  data = 0;
  ledcWrite(12, 0);
  ledcWrite(13, 0);
  ledcWrite(14, 0);
  ledcWrite(15, 0);
  motor_update(data);
}

void motor_update(byte dataout) {
  digitalWrite(15, 1); //output idle
  digitalWrite(19, 0); //latchpin activated. transmission started
  digitalWrite(14, 0); //data idle
  digitalWrite(4, 0); //clock idle

  //serial register input
  bool pinState;
  for (int i = 7; i >= 0; i--)  {
    digitalWrite(4, 0); //preparing the clock
    (dataout & (1 << i)) ? pinState = 1 : pinState = 0; //comparator
    digitalWrite(14, pinState); //desired data signal
    digitalWrite(4, 1); //rising edge trigger
    digitalWrite(14, 0); //data pin kept low to prevent overflowing
  }
  digitalWrite(4, 0);
  digitalWrite(19, 1); //transmission idle
  digitalWrite(15, 0); //output active
}
