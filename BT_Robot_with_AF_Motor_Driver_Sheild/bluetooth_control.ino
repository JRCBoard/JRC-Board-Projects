void bluetooth_control() {
  SerialBT.begin("Bluetooth RC Car");
  int s = 10, spdl = 25, spdr = 25;
  while (1) {
    if (SerialBT.available()) {
      char x = SerialBT.read();
      Serial.println(x);
      if (x == 'F') motor(s * spdl, s * spdr);
      else if (x == 'B') motor(-s * spdl, -s * spdr);
      else if (x == 'L') motor(-s * spdl, s * spdr);
      else if (x == 'R') motor(s * spdl, -s * spdr);
      else if (x == 'G') motor(0, s * spdr);
      else if (x == 'I') motor(s * spdl, 0);
      else if (x == 'H') motor(0, -s * spdr);
      else if (x == 'J') motor(-s * spdl, 0);
      else if (x == 'S') motor_stop();
      else if (x == 'W') digitalWrite(18, HIGH);
      else if (x == 'w') digitalWrite(18, LOW);
      else if (x == '0') s = 0;
      else if (x == '1') s = 1;
      else if (x == '2') s = 2;
      else if (x == '3') s = 3;
      else if (x == '4') s = 4;
      else if (x == '5') s = 5;
      else if (x == '6') s = 6;
      else if (x == '7') s = 7;
      else if (x == '8') s = 8;
      else if (x == '9') s = 9;
      else if (x == 'q') s = 10;
    }
  }
}
