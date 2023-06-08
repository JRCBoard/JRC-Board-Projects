void snake_game() {
  bool menu = 1;
p: len = 4;
  while (digitalRead(sw[0])) {
    m82 = millis();
    display.clearDisplay();
    text("GAME MODE?", 04, 0);
    text("   EASY   ", 04, 25);
    text("   HARD   ", 04, 50);
    (dl >= 100) ? text(">>      <<", 04, 25) : text(">>      <<", 04, 50);
    display.display();
    if (!digitalRead(sw[1]) && menu != 0) {
      dl = 50; digitalWrite(buzzer, HIGH); m83 = m82; menu = 0;
    }
    else if (!digitalRead(sw[3]) && menu != 1) {
      dl = 100; digitalWrite(buzzer, HIGH); m83 = m82; menu = 1;
    }
    if (m82 - m83 > beep) digitalWrite(buzzer, LOW);
  }
  while (!digitalRead(sw[0]));
  while (1) {
    if (eat == 1) {
      food(); digitalWrite(buzzer, HIGH); m83 = millis();
    }
    else digitalWrite(buzzer, LOW);
    draw();
    motion();
    button();
    for (short int i = 1; i < len ; i ++)
      if (pos[0] == pos[i]) {
        if (game_over(len - 4) == 1) {
          len = 4; goto p;
        }
        len = 4;
      }
  }
}
