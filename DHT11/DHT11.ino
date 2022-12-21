#include <DHT.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13,14,15,16,17,4);
DHT dht(23, DHT11);
void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
}

void loop() {
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("HUMIDITY   TEMP");
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(1,1);
  lcd.print(String(h) + "%");
  lcd.setCursor(10,1);
  lcd.print(String(t) + "C");
}
