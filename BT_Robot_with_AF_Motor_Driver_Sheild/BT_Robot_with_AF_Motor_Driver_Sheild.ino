#include <BluetoothSerial.h>
BluetoothSerial SerialBT;
byte data = 0b00000000;

void setup() {
  Serial.begin(9600);
  pinMode(18, OUTPUT);
  digitalWrite(18, HIGH); //to indicate that bluetooth actually started
  pinMode(19, OUTPUT); // latchpin
  pinMode(15, OUTPUT); //output enable pin
  pinMode(4, OUTPUT); //clockpin
  pinMode(14, OUTPUT); //datapin
  digitalWrite(15, 1); //output idle
  digitalWrite(19, 1); //latchpin idle
  digitalWrite(14, 0); //data idle
  digitalWrite(4, 0); // clock idle
  //setting up all the respective pwm pins
  ledcSetup(12, 5000, 8);
  ledcSetup(13, 5000, 8);
  ledcSetup(14, 5000, 8);
  ledcSetup(15, 5000, 8);
  ledcAttachPin(23, 12);
  ledcAttachPin(2, 13);
  ledcAttachPin(16, 14);
  ledcAttachPin(17, 15);
  motor_stop();
//  motor1(1,255);
  bluetooth_control();
  
}

void loop() {
}
