#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("LED remote"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(18, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(15, LOW);

}

void loop() {
  if (SerialBT.available()) {
    char x = SerialBT.read();
    Serial.print(x);
    if (x == '1') digitalWrite(18, HIGH);
    else if (x == 'A')digitalWrite(18, LOW);
    else if (x == '2') digitalWrite(14, HIGH);
    else if (x == 'B')digitalWrite(14, LOW);
    else if (x == '3') digitalWrite(2, HIGH);
    else if (x == 'C')digitalWrite(2, LOW);
    else if (x == '9') {
      digitalWrite(18, HIGH);
      digitalWrite(14, HIGH);
      digitalWrite(2, HIGH);
    }
    else if (x == 'I') {
      digitalWrite(18, LOW);
      digitalWrite(14, LOW);
      digitalWrite(2, HIGH);
    }
  }
}
