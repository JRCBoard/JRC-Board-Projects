#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define lmf 0
#define lmb 16
#define lms 15
#define rms 02
#define rmf 17
#define rmb 04
#define sw 19
#define led1 14
#define led2 32

void setup() {
  Serial.begin(9600);
  SerialBT.begin("Bluetooth Car 1");
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
  bluetooth();
}

void loop() {
  if (SerialBT.available()) bluetooth();
}
