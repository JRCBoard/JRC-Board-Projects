byte push(byte a) {
  uint32_t timer = 0;
  if (!digitalRead(a)) {
    delay(50);
    while (!digitalRead(a)) {
      digitalWrite(18, 1);
      delay(20);
      timer += 20;
      if (timer > 3000) return 2;
    }
    digitalWrite(18, 0);
    if(timer) return 1;
    else return 0;
  }
}