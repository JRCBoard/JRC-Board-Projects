void led_level(int a) {
  int p;

  for (byte i = 0; i < 6; i++) {
    if (a >= i * 14) {
      (a > (i + 1) * 14) ? p = (i + 1)* 14 : p = a;
      p = map(p, i * 14, (i + 1) * 14, 0, 255);
      ledcWrite(i, p);
    } else ledcWrite(i, 0);
  }

  if (a >= 84) {
    (a > 100) ? p = 100 : p = a;
    p = map(p, 84, 100, 0, 255);
    ledcWrite(6, p);
  } else ledcWrite(6, 0);
}