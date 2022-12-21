void bluetooth() {
  SerialBT.begin("Grabber BOT");
  int s = 10, i = 9, temp = 0, spdl = 25, spdr = 25; digitalWrite(led, 1);
  while (digitalRead(sw)) {
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
      else if (x == 'S') motor(0, 0);
      else if (x >= '0' && x <= '9') temp = x - '0';
      else if (x == 'q') temp = 10;
      if (i != temp) {
        i = temp;
        lservo.write(lpos[i]);
        rservo.write(rpos[i]);
      }
    }
  }
  digitalWrite(led, 0);
  SerialBT.end();
}
