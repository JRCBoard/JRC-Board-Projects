void status_check() {
  if (WiFi.status() == WL_CONNECTED) {
    lcd.setCursor(15, 0);
    lcd.print(char(219));
    Serial.println(WiFi.localIP());
  }

  else {
    lcd.setCursor(15, 0);
    lcd.print(" ");
  }
}