int game_over(int a) {
  for (byte i = 0; i < 5 ; i++) {
    digitalWrite(buzzer, HIGH);
    delay(beep);
    digitalWrite(buzzer, LOW);
    delay(beep);
  }
  value = String(a);
  int menu = 0;
  while (digitalRead(sw[1]) && digitalRead(sw[3])) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    text("GAME OVER!", 04, 0);
    text("SCORE:" + value, 04, 25);
    display.setTextSize(1);
    text(" PLAY AGAIN", 04, 55);
    text("              EXIT", 04, 55);
    (menu == 0) ? text(">          <", 04, 55) : text("             >    <", 04, 55);
    display.display();
    if (!digitalRead(sw[0])) menu = 1;
    else if (!digitalRead(sw[2])) menu = 0;
  }
  while (!digitalRead(sw[1]) || !digitalRead(sw[3]));
  display.setTextSize(2);
  return menu;
}
