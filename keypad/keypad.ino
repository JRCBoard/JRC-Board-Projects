#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
char nums[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[4] = {15, 16, 17, 4}; //connect to the row pinouts of the keypad
byte colPins[4] = {18, 19, 23, 5}; //connect to the column pinouts of the keypad
char wd[255];
char w;
char key, temp;
uint32_t t1;
byte count = 0;
byte addition;
int timer = 500;
byte scroll;
bool state;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 4 );

void setup()
{
  lcd.init();
  lcd.backlight();
  analogWrite(25, 255); delay(1000); analogWrite(25, 0); delay(100);
  lcd.setCursor(0, 0);
  lcd.blink();
  pinMode(13, OUTPUT);
  keypad.addEventListener(keypadEvent);
  Serial.begin(115200);
  SerialBT.begin("sender",true);
  bool connected = SerialBT.connect("receiver");
  if (connected) {
    Serial.println("Connected!");
    analogWrite(25, 255); delay(100); analogWrite(25, 0); delay(100);
    analogWrite(25, 255); delay(100); analogWrite(25, 0); delay(100);
    analogWrite(25, 255); delay(100); analogWrite(25, 0);
  }

}


void loop()
{
  key = keypad.getKey();
  if (Serial.available()) {
    count = 0; state = 1;
    while (1) {
      wd[count] = Serial.read();
      if (wd[count] == 59) break;
      count++;
    }
    show_message(scroll);
    while (state) {
      key = keypad.getKey();
    }
  }
  if (SerialBT.available()) {
    count = 0; state = 1;
    for(int i=0; i<
    wd[count] = SerialBT.read();
    count++;
    while (1) {
      if (SerialBT.available()) {
        wd[count] = SerialBT.read();
        if (wd[count] == 59) break;
        count++;
      }
    }
    show_message(scroll);
    while (state) {
      key = keypad.getKey();
    }
  }
}
