//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  //  analogReadResolution(8);
  lcd.init();
  lcd.backlight();
}


void loop() {
  int x = analogRead(32);
  x = map(x, 0, 4095, 0, 100);
  lcd.setCursor(0, 0);
  lcd.print("READING: ");
  if (x < 10) lcd.print(String(x) + "   ");
  else if (x < 100) lcd.print(String(x) + "  ");
  else if (x < 1000) lcd.print(String(x) + " ");
  else lcd.print(String(x));
  //  delay(500);
}
