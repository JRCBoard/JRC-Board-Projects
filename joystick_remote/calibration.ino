void cal() {
  m1 = millis();
  while (1) {
    if (millis() - m1 > 3000) break;
    if (millis() - m2 > 200) {
      m2 = millis(); digitalWrite(13, !digitalRead(13));
    }
    for (byte i = 0; i < 2; i++) {
      joystick[i] = analogRead(joystick_pin[i]);
      if (joystick[i] > joy_max[i]) joy_max[i] = joystick[i];
      if (joystick[i] < joy_min[i]) joy_min[i] = joystick[i];
    }
  }
  joy_max[0] -= 50; joy_max[1] -= 50;
  joy_min[0] += 50; joy_min[1] += 50;
  joy_mid[0] = ((joy_max[0] + joy_min[0]) / 2) - 100;
  joy_mid[1] = ((joy_max[1] + joy_min[1]) / 2) - 100;
}
