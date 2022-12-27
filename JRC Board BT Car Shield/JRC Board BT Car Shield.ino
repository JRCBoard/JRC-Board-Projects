#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define lmf 0
#define lmb 16
#define lms 15
#define rms 2
#define rmf 17
#define rmb 4
#define sw 19
#define led1 14
#define led2 32

void setup() {
  Serial.begin(9600);
  SerialBT.begin("BRC");
  ledcSetup(0, 1000, 8);
  ledcSetup(1, 1000, 8);
  ledcAttachPin(lms, 0);
  ledcAttachPin(rms, 1);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  motor(0, 0);
  bluetooth();
}

void loop() {
}
