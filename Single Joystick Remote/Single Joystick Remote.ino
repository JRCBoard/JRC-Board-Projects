#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
byte x, y, xstate, ystate;
int red=4,green=15,blue=17,gnd=16;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(gnd, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  digitalWrite(26, 0);
  digitalWrite(25, 1);
  digitalWrite(gnd, 0);
  Serial.begin(9600);
  SerialBT.begin("remote master", true);
p:    bool connected = SerialBT.connect("Bluetooth RC Car");
  if (connected) digitalWrite(18, 1);
  else goto p;

}

void loop() {
  if (analogRead(34) > 2500) y = 2;
  else if (analogRead(34) < 1500) y = 1;
  else y = 0;
  if (analogRead(35) > 2500) x = 2;
  else if (analogRead(35) < 1500) x = 1;
  else x = 0;
  if (x != xstate || y != ystate) {
    xstate = x; ystate = y;
    if (y == 0 && x == 0) {
      SerialBT.write('S');
      digitalWrite(red, 1);
      digitalWrite(green, 1);
      digitalWrite(blue, 1);
    }
    else if (y == 2 && x == 0) {
      SerialBT.write('F');
      digitalWrite(red, 0);
      digitalWrite(green, 1);
      digitalWrite(blue, 1);
    }
    else if (y == 1 && x == 0) {
      SerialBT.write('B');
      digitalWrite(red, 0);
      digitalWrite(green, 0);
      digitalWrite(blue, 0);
    }
    else if (y == 0 && x == 2) {
      SerialBT.write('L');
      digitalWrite(red, 1);
      digitalWrite(green, 0);
      digitalWrite(blue, 1);
    }
    else if (y == 0 && x == 1) {
      SerialBT.write('R');
      digitalWrite(red, 1);
      digitalWrite(green, 1);
      digitalWrite(blue, 0);
    }
    else if (y == 2 && x == 2) {
      SerialBT.write('G'); // forward left
      digitalWrite(red, 0);
      digitalWrite(green, 0);
      digitalWrite(blue, 1);
    }
    else if (y == 2 && x == 1) {
      SerialBT.write('I'); // forward right
      digitalWrite(red, 0);
      digitalWrite(green, 1);
      digitalWrite(blue, 0);
    }
    else if (y == 1 && x == 2) {
      SerialBT.write('H'); // backward left
      digitalWrite(red, 1);
      digitalWrite(green, 0);
      digitalWrite(blue, 1);
    }
    else if (y == 1 && x == 2) {
      SerialBT.write('J'); // backward right
      digitalWrite(red, 1);
      digitalWrite(green, 1);
      digitalWrite(blue, 0);
    }
    delay(30);
  }
}
