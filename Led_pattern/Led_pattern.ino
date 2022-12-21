byte ledhigh[6] = {19, 5, 14, 16, 4, 0};
byte ledlow[6] = {18, 23, 13, 15, 17, 2};

void setup() {
  for (byte i = 0; i < 6; i++) {
    pinMode(ledlow[i], OUTPUT);
    digitalWrite(ledlow[i], 0);
  }
  for (byte i = 0; i < 6 ; i++) {
    ledcSetup(i, 1000, 3);
    ledcAttachPin(ledhigh[i], i);
  }
}

void loop() {
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      if (i - j == 0) ledcWrite(j, 7);
      else if ((i - j == 1) || (j - i == 1)) ledcWrite(j, 4);
      else if ((i - j == 2) || (j - i == 2)) ledcWrite(j, 1);
      else ledcWrite(j, 0);
    }
    delay(100);
  }
  for (int i = 5; i >=0; i--) {
    for (int j = 0; j < 6; j++) {
      if (i - j == 0) ledcWrite(j, 7);
      else if (i - j == 1 || j - i == 1) ledcWrite(j, 4);
      else if (i - j == 2 || j - i == 2) ledcWrite(j, 1);
      else ledcWrite(j, 0);
    }
    delay(100);
  }

}
