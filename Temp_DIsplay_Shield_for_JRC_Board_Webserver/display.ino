void display() {
  lcd.setCursor(0, 0);
  lcd.print("TEMP: " + String(temp) + char(223) + "C");
  lcd.setCursor(0, 1);
  lcd.print("HUMID: " + String(humidity) + "%");
}