#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int trig = 33, echo = 32;
void setup() {
 pinMode(trig, OUTPUT);
 pinMode(echo, INPUT);
// pinMode(4, OUTPUT);
// digitalWrite(4, 0);
 Serial.begin(9600);
 lcd.init(); lcd.backlight();
}
void loop() {
 lcd.setCursor(0,0);
 lcd.print("Distance:");
 int x = reading();
 lcd.print(String(x));
 lcd.print("cm   ");
 lcd.setCursor(0,1);
 (x<5 && x!=0)? lcd.print("   WARNING!!!   ") : lcd.print("                ");
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
