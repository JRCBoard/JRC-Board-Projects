void myTimerEvent() {
  Blynk.virtualWrite(V10, millis() / 1000);
}

void statUpdate() {
  for (int i = 0; i < count; i++)
    if (state[i] != value[i]) {
      value[i] = state[i];
      Blynk.virtualWrite(i * 2, value[i]);    //v1
      Blynk.virtualWrite(i * 2 + 1, value[i]); //v3

    }
}

BLYNK_WRITE(0) {
  value[0] = param.asInt();
  state[0] = value[0];
  Blynk.virtualWrite(1, value[0]);
}
BLYNK_WRITE(2) {
  value[1] = param.asInt();
  state[1] = value[1];
  Blynk.virtualWrite(3, value[1]);
}
BLYNK_WRITE(4) {
  value[2] = param.asInt();
  state[2] = value[2];
  Blynk.virtualWrite(5, value[2]);
}
