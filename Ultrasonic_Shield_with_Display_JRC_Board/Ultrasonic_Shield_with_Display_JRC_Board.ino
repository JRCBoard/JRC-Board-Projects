#include <LiquidCrystal.h>
LiquidCrystal lcd(5, 14, 15, 16, 17, 4);
const int trig = 19, echo = 18, buzzer = 26;

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(115200);
  lcd.begin(16, 2);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  int x = read2ing();
  lcd.print(String(x));
  Serial.println("Distance: " + String(x) + "cm");
  lcd.print("cm   ");
  lcd.setCursor(0, 1);
  (x < 5 && x != 0) ? lcd.print("   WARNING!!!   ") : lcd.print("                ");
  (x < 5 && x != 0) ? digitalWrite(buzzer, 1) : digitalWrite(buzzer, 0);
  delay(100);
}

int reading() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH);
  int distance = duration * 0.0343 / 2;
  return distance;
}
