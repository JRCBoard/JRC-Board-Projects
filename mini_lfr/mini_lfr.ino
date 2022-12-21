#include<EEPROM.h>
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define lmf 2
#define lmb 4
#define lms 0
#define rms 15
#define rmf 17
#define rmb 16
#define sw 19
#define led 5

#define spl 25 //left motor speed coeficient
#define spr 15 //right motor speed coeficient
#define dr 3 //straightner coefficient
#define wait 20 //waiting time for robot to go forward before making a turn
#define tsp 100
#define tbr 40
#define side 2
int maximum[6], minimum[6], mid[6] = {1500, 1500, 1500, 1500, 1500, 1500};
char flag = 's';
int pos;


int s[6];
int base[6] = {1, 2, 4, 8, 16, 32}; //this is for binary to decimal conversion
int sensor; //this is to store final value after binary conversion
int sum = 0; //this is to store the count of detected sensor
unsigned long m1, m2, m3;

void setup() {
  Serial.begin(9600);
  EEPROM.begin(20);
  ledcSetup(0, 100, 8);
  ledcSetup(1, 100, 8);
  ledcAttachPin(lms, 0);
  ledcAttachPin(rms, 1);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  pinMode(23, OUTPUT);
  digitalWrite(23, 0);
  //robot starting indicator
  digitalWrite(led, 1); delay(100);
  digitalWrite(led, 0); delay(100);
  digitalWrite(led, 1); delay(100);
  digitalWrite(led, 0); delay(100);
  motor(0, 0);
  for (int i = 0; i < 6; i++) {
    mid[i] = EEPROM.read(i) * 16;
    maximum[i] = EEPROM.read(i + 6) * 16;
    minimum[i] = EEPROM.read(i + 12) * 16;
    Serial.println(String(maximum[i]) + " " + String(mid[i]) + " " + String(minimum[i]));
  }
}

void loop() {
  int r = push();
  if (r != 0) {
    if (r == 1) line_follow();
    else if (r == 2) bluetooth();
    else if (r == 3) cal();
    else if (r == 4) motor(10 * spl, 10 * spr);
    else if (r == 5) motor(-10 * spl, -10 * spr);
    else if (r == 6) while (digitalRead(sw)) digital_value();
    else if (r == 7) while (digitalRead(sw)) analog_value();
    while (!digitalRead(sw)) motor(0,0);
  }
}
