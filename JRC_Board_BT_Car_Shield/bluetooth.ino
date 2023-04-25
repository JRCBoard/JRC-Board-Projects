void bluetooth() {
  int s = 10, spdl = 25, spdr = 25;
  light(1);
  delay(100);
  light(0);
  delay(100);
  light(1);
  delay(100);
  light(0);
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
      else if (x == 'J') motor(0, -s * spdr);
      else if (x == 'H') motor(-s * spdl, 0);
      else if (x == 'S') motor(0, 0);
      else if (x == 'W') light(1);
      else if (x == 'w') light(0);
      else if (x >= '0' && x <= '9') s = x - '0';
      else if (x == 'q') s = 10;
    }
  }
  digitalWrite(led1, 0);
  digitalWrite(led2, 0);
}
