#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
uint32_t m1, m2;
int joystick_pin[] = {35, 33};
int joystick[2];
int joy_min[2] = {4096, 4096};
int joy_max[2] = {0, 0};
int joy_mid[2];
byte stat[2];
int error = 200;
long int fsp, ssp;
int dir, t_dir;
void setup() {
  pinMode(13, OUTPUT);
  pinMode(14, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  cal();
  Serial.begin(9600);
  SerialBT.begin("joystick remote", true);
  bool connected = SerialBT.connect("Bluetooth RC Car");
  if (connected) digitalWrite(13, 1);
}

void loop() {
  stat[0] = front(); stat[1] = side();
  Serial.println(String(stat[0]) + " " + String(stat[1]) + " " + String(dir) + " " + String(fsp) + " " + String(ssp));
  dir = (stat[0] % 10) * 10 + (stat[1] % 10);

  if (fsp != stat[0] / 10) {
    fsp = stat[0] / 10;
    if (dir % 10 == 1) {
      if (fsp == 10) SerialBT.write('q');
      else SerialBT.write('0' + fsp);
      if (dir == 21) SerialBT.write('F');
      else if (dir == 01) SerialBT.write('B');
    }
  }

  if (ssp != stat[1] / 10) {
    ssp = stat[1] / 10;
    if (dir / 10 == 1) {
      if (ssp == 10) SerialBT.write('q');
      else SerialBT.write('0' + ssp);
      if (dir == 12) SerialBT.write('L');
      else if (dir == 10) SerialBT.write('R');
    }
  }

  if (t_dir != dir) {
    t_dir = dir;
    if (t_dir == 11) SerialBT.write('S');
    else if (t_dir == 21) SerialBT.write('F');
    else if (t_dir == 01) SerialBT.write('B');
    else if (t_dir == 12) SerialBT.write('L');
    else if (t_dir == 10) SerialBT.write('R');
    else {
      SerialBT.write('q');
      if (t_dir == 22) SerialBT.write('G');
      else if (t_dir == 02) SerialBT.write('H');
      else if (t_dir == 20) SerialBT.write('I');
      else if (t_dir == 00) SerialBT.write('J');
    }
  }
  delay(20);
}
