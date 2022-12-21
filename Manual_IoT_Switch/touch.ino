bool touchSense(int a) {
  int touchValue = touchRead(a);
  Serial.print(String(touchValue) + " ");
  if (touchValue < threshold) return 1;
  else return 0;
}

void touchUpdate() {
  for (int i = 0; i < count; i++) {
    int t = 0;
    while (touchSense(button[i])) {
      delay(1); t++;
    }
    if (t > 15) state[i] = !state[i];
  }
  Serial.println();
}
