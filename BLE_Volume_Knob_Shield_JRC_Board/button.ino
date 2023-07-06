bool push(byte button) {
  int t = 0;
  bool flag = 1;
  if (!digitalRead(button)) {
    delay(50);  //debounce delay
    while (!digitalRead(button)) {
      delay(10);
      t++;
      led_level(t);
      if (t > 100 && flag) {
        flag = 0;
        present_mode = !present_mode;
        digitalWrite(indicator, !present_mode);
        (!present_mode) ? led_level(14) : led_level(0);
        encoder.setCount(25);
      }
    }
    if (t > 0 && t < 100) {
      (!present_mode) ? led_level(volume) : led_level(0);
      return 1;
    }
  }
  return 0;
}
