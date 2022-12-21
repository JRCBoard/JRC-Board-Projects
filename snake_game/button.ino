void button() {
  m81 = m82 = millis();
  while (m82 - m81 < dl) {
    m82 = millis();
    if (digitalRead(sw[3]) && dir != 4 && dir != 2) {
      dir = 2; digitalWrite(buzzer, HIGH); m83 = millis();
    }
    if (digitalRead(sw[2]) && dir != 1 && dir != 3) {
      dir = 1; digitalWrite(buzzer, HIGH); m83 = millis();
    }
    if (digitalRead(sw[1]) && dir != 4 && dir != 2) {
      dir = 4; digitalWrite(buzzer, HIGH); m83 = millis();
    }
    if (digitalRead(sw[0]) && dir != 1 && dir != 3) {
      dir = 3; digitalWrite(buzzer, HIGH); m83 = millis();
    }
    if (m82 - m83 > beep) digitalWrite(buzzer, LOW);
  }
}
