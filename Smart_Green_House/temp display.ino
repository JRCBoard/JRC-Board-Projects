void temp_display(){
  //for showing temparature
  lcd.setCursor(0,0);
  lcd.print("TEMP: ");
  lcd.print(t);
  lcd.print(" C");
  //for showing humidity
  lcd.setCursor(0,1);
  lcd.print("HUMIDITY: ");
  lcd.print(h);
  lcd.print("%");
}