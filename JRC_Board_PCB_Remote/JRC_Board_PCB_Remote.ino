#include "EEPROM.h"
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
uint32_t m1, m2;
byte joystick_pin[2] = { 34, 32 };
byte joy_button[2] = { 25, 5 };
int joystick[2];
int joy_min[2], joy_max[2], joy_mid[2];
byte stat[2];
int error = 200;
long int fsp, ssp;
int dir, t_dir;

void setup() {
  EEPROM.begin(32);
  for (byte i = 0; i < 2; i++) {
    joy_mid[i] = EEPROM.read(i) * 16;
    joy_min[i] = EEPROM.read(i + 2) * 16;
    joy_max[i] = EEPROM.read(i + 4) * 16;
  }

  pinMode(13, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(joy_button[0], INPUT_PULLUP);
  pinMode(joy_button[1], INPUT_PULLUP);
  Serial.begin(115200);
  SerialBT.begin("JRC Board Remote Kit 2", true);
  bool connected = SerialBT.connect("JRC Car 2");
  if (connected) digitalWrite(13, 1);
}

void loop() {
  stat[0] = front();
  stat[1] = side();
  Serial.println(String(dir) + " " + String(fsp) + " " + String(ssp));
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

  byte x = push(joy_button[0]);
  if (x == 1) SerialBT.write('w');
  else if (x == 2) cal();

  x = push(joy_button[1]);
  if (x == 1) SerialBT.write('W');
  else if (x == 2) cal();

  delay(20);
}
