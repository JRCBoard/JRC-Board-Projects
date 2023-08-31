void cal() {
  m1 = millis();
  for (byte i = 0; i < 2; i++) {
    joy_max[i] = 0;
    joy_min[i] = 4095;
  }
  while (1) {
    if (millis() - m1 > 3000) break;
    if (millis() - m2 > 200) {
      m2 = millis();
      digitalWrite(13, !digitalRead(13));
    }
    for (byte i = 0; i < 2; i++) {
      joystick[i] = analogRead(joystick_pin[i]);
      if (joystick[i] > joy_max[i]) joy_max[i] = joystick[i];
      if (joystick[i] < joy_min[i]) joy_min[i] = joystick[i];
    }
  }
  
  for (byte i = 0; i < 2; i++) {
    joy_max[i] -= 50;
    joy_min[i] += 50;
    joy_mid[i] = ((joy_max[i] + joy_min[i]) / 2) - 100;
    EEPROM.write(i, joy_mid[i]/16);
    EEPROM.write(i+2, joy_max[i]/16);
    EEPROM.write(i+4, joy_min[i]/16);
  }
  
  EEPROM.commit();
}
