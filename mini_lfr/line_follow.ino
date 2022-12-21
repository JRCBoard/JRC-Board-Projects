void line_follow() {
  while (1) { //infinite loop
a:    reading();
    if (sum == 0) {
      if (flag != 's') {
        delay(wait);
        (flag == 'l') ? motor(-tsp, tsp) : motor(tsp, -tsp);
        while (s[2] == 0 && s[3] == 0) reading();
        (flag == 'l') ? motor(tsp, -tsp) : motor(-tsp, tsp); delay(tbr);
        pos = 0; flag = 's'; //when you are done turning robot, make the flag to its normal state so that robot wont turn on its own when it finds no line without detecting 90degree logic
      }
    }
    else if (sum == 1 || sum == 2) {
      if (sensor == 0b001100) {
        if (pos != 0) {
          (pos > 0) ? motor(-10 * spl, 10 * spr) : motor(10 * spl, -10 * spr);
          (pos > 0) ? delay(pos * dr) : delay(-pos * dr); pos = 0; //this logic is for those whose bot is wabbling during high speed run. this logic will forcefully return bot to its midpoint. don't give more than 30ms delay here!
        }
        motor(10 * spl, 10 * spr); 
      }
      //right side portion
      else if (sensor == 0b000100) {
        motor(10 * spl, 8 * spr); 
      }
      else if (sensor == 0b000110) {
        if (pos < 1) pos = 1; motor(10 * spl, 5 * spr);
      }
      else if (sensor == 0b000010) {
        if (pos < 2) pos = 2; motor(10 * spl, 2 * spr);
      }
      else if (sensor == 0b000011) {
        if (pos < 3) pos = 3; motor(10 * spl, -2 * spr);
      }
      else if (sensor == 0b000001) {
        if (pos < 4) pos = 4; motor(10 * spl, -5 * spr);
      }
      //left side portion
      else if (sensor == 0b001000) {
        motor(8 * spl, 10 * spr); 
      }
      else if (sensor == 0b011000) {
        if (pos > -1) pos = -1; motor(5 * spl, 10 * spr);
      }
      else if (sensor == 0b010000) {
        if (pos > -2) pos = -2; motor(2 * spl, 10 * spr);
      }
      else if (sensor == 0b110000) {
        if (pos > -3) pos = -3; motor(-2 * spl, 10 * spr);
      }
      else if (sensor == 0b100000) {
        if (pos > -4) pos = -4; motor(-5 * spl, 10 * spr); 
      }
    }

    else if (sum == 3 || sum == 4 || sum == 5) { //only for sharp turn logic
      if (s[0] == 0 && s[5] == 1 && s[2] + s[3] > 0) flag = 'l';
      else if (s[0] == 1 && s[5] == 0 && s[2] + s[3] > 0) flag = 'r';
      m1 = millis();
    }

    else if (sum == 6) {
      m3 = millis(); flag = 's'; pos = 0;
      while (s[0] == 1 || s[5] == 1) {
        reading(); m2 = millis();
        if (m2 - m3 > 200) {
          motor(0, 0); digitalWrite(led, HIGH);
          while (sum == 6) reading();
          digitalWrite(led, LOW); delay(1000); goto a;
        }
      }
      m1 = millis();
    }
    m2 = millis();
    if (m2 - m1 > 200) flag = 's';
  }
}
