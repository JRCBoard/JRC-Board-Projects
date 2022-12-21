#include<EEPROM.h>
#include <ESP32Servo.h>
#include <BluetoothSerial.h>
BluetoothSerial SerialBT;
Servo lservo;
Servo rservo;

#define lpwm 6
#define rpwm 7
#define lmf 16
#define lmb 15
#define lms 17
#define rms 4
#define rmf 0
#define rmb 2
#define sw 19
#define led 5

#define spl 25 //left motor speed coeficient
#define spr 25 //right motor speed coeficient
#define dr 3 //straightner coefficient
#define wait 20 //waiting time for robot to go forward before making a turn
#define tsp 100
#define tbr 40
#define side 2
int maximum[6], minimum[6], mid[6] = {3500, 3500, 3500, 3500, 3500, 3500};
char flag = 's';
int pos;
int lpos[11] = {180, 169, 158, 147, 136, 125, 114, 103, 92, 81, 70};
int rpos[11] = {0, 11, 22, 33, 44, 55, 66, 77, 88, 99, 110};


int s[6];
int base[6] = {1, 2, 4, 8, 16, 32}; //this is for binary to decimal conversion
int sensor; //this is to store final value after binary conversion
int sum = 0; //this is to store the count of detected sensor
unsigned long m1, m2, m3;

void setup() {
  lservo.attach(14, 500, 2400); rservo.attach(13, 500, 2400);
  lservo.write(lpos[0]); rservo.write(rpos[0]);
  Serial.begin(9600);
  EEPROM.begin(20);
  ledcSetup(lpwm, 100, 8);
  ledcSetup(rpwm, 100, 8);
  ledcAttachPin(lms, lpwm);
  ledcAttachPin(rms, rpwm);
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
    //    mid[i] = EEPROM.read(i) * 16;
    mid[i] = 4000;
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
    else if (r == 4) while (digitalRead(sw)) motor(10 * spl, 10 * spr);
    else if (r == 5) while (digitalRead(sw)) motor(-5 * spl, -5 * spr);
    else if (r == 6) while (digitalRead(sw)) digital_value();
    else if (r == 7) while (digitalRead(sw)) analog_value();
    else if (r == 8) while (digitalRead(sw)) {
        for (int i = 0; i <= 10; i++) {
          lservo.write(lpos[i]); delay(10);
        }
        for (int i = 10; i >= 0; i--) {
          lservo.write(lpos[i]); delay(10);
        }
        for (int i = 0; i <= 10; i++) {
          rservo.write(rpos[i]); delay(10);
        }
        for (int i = 10; i >= 0; i--) {
          rservo.write(rpos[i]); delay(10);
        }
      }
    while (!digitalRead(sw)) motor(0, 0);
  }
}
