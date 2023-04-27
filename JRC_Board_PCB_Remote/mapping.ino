int mapping(int a, int b, int c, int d, int e) {
  float ratio = (float)(e - d) / (float)(c - b);
  if (a < b) a = b;
  if (a > c) a = c;
  a = (a - b) * ratio;
  return a;
}

byte front() {
  byte a, b;
  joystick[0] = analogRead(joystick_pin[0]);
  if (joystick[0] < joy_mid[0] + error && joystick[0] > joy_mid[0] - error) return 1;
  else if (joystick[0] <= joy_mid[0] - error) {
    a = 0;
    b = mapping(joystick[0], joy_min[0], joy_mid[0] - error, 0, 10);
    b = 10 - b;
    return b * 10 + a;
  }
  else if (joystick[0] >= joy_mid[0] + error) {
    a = 2;
    b = mapping(joystick[0], joy_mid[0] + error, joy_max[0], 0, 10);
    return b * 10 + a;
  }
}

byte side() {
  byte a, b;
  joystick[1] = analogRead(joystick_pin[1]);
  if (joystick[1] < joy_mid[1] + error && joystick[1] > joy_mid[1] - error) return 1;
  else if (joystick[1] <= joy_mid[1] - error) {
    a = 2;
    b = mapping(joystick[1], joy_min[1], joy_mid[1] - error, 0, 10);
    b = 10 - b;
    return b * 10 + a;
  }
  else if (joystick[1] >= joy_mid[1] + error) {
    a = 0;
    b = mapping(joystick[1], joy_mid[1] + error, joy_max[1], 0, 10);
    return b * 10 + a;
  }
}
