#include <LiquidCrystal.h>
#include <ESP32Servo.h>
#include <DHT.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define fan_pin 15
#define DHTPIN 32
#define ServoPin 33

DHT dht(DHTPIN, DHT11);
LiquidCrystal lcd(14, 13, 5, 23, 19, 18);
Servo myservo;



unsigned long timer1;
float t, h;
bool mode = 0;

void setup() {
  //for Serial monitor and bluetooth
  Serial.begin(115200);
  SerialBT.begin("Green House");

  //for LCD Display
  lcd.begin(16, 2);

  //for Servo Motor
  myservo.setPeriodHertz(50);            // standard 50 hz servo
  myservo.attach(ServoPin, 1000, 2000);  // attaches the servo on pin 18 to the servo object
  myservo.write(90);

  //for temparature sensor
  dht.begin();

  //for exhaust fan
  pinMode(fan_pin, OUTPUT);

  //to keep track of the time
  timer1 = millis();

  //starting screen
  lcd.print("JRC Board, The Problem Solver");
}

void loop() {
  char x = SerialBT.read();
  Serial.print(x);
  if (x == '8') {
    lcd.clear();
    mode = 1;
  }

  else if (x == 'H') {
    lcd.clear();
    lcd.print("JRC Board, The Problem Solver");
    mode = 0;
  }

  else if (x == '1') myservo.write(30);
  else if (x == 'A') myservo.write(180);
  else if (x == '2') digitalWrite(fan_pin, 1);
  else if (x == 'B') digitalWrite(fan_pin, 0);


  if (millis() - timer1 > 2000) {
    timer1 = millis();
    t = dht.readTemperature();
    h = dht.readHumidity();
    if (mode) temp_display();
  }

  if (!mode) {
    lcd.scrollDisplayLeft();
    delay(500);
  }

  if(t > 30) digitalWrite(fan_pin, 1);
  else if(t < 25) digitalWrite(fan_pin, 0);
}
