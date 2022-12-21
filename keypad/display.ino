void display_update() {
  lcd.clear();
  lcd.setCursor(0, 0);
  for (byte i = (count / 32) * 32; i < count; i++) {
    if (i % 32 == 16) lcd.setCursor(0, 1);
    lcd.print(wd[i]);
  }
}

void show_message(byte a) {
  lcd.clear(); lcd.setCursor(0, 0);
  if (a <= count / 32)
    for (int i = a * 32; i < a * 32 + 32; i++) {
      if (i % 32 == 16) lcd.setCursor(0, 1);
      if (i == count) break;
      lcd.print(wd[i]);
    }
}
