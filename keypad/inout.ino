void keypadEvent(KeypadEvent key) {
  switch (keypad.getState()) {
    case PRESSED:
      if (key == 'D') {
        if (count > 0) count --;
        wd[count] = 32;
        display_update();
      }
      else if (key == 'B' && state) {
        scroll++;
        if (scroll > (count / 32) + 1) scroll = 0;
        show_message(scroll);
      }
      else if (key == 'C' && state) {
        scroll--;
        if (scroll < 0 ) scroll = (count / 32) + 1;
        show_message(scroll);
      }
      else if (key == '#' && state) {
        state = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        count = 0;
      }
      else if (key == 'A') {
        wd[count] = 59; count++;
        for (byte i = 0; i < count; i++) {
          Serial.print(wd[i]);
          SerialBT.write(wd[i]);
          wd[i] = 0;
        }
        lcd.clear();
        lcd.setCursor(0, 0);
        count = 0;
      }
      else {
        w = key;
        if (key == '1') wd[count] = 46;
        else if ( key == '2') {
          if (temp == key && millis() - t1 < timer) {
            count--; wd[count]++;
            if (wd[count] == 'D') wd[count] = key;
            else if (wd[count] == key) wd[count] = 'A';
          }
          else {
            wd[count] = 'A'; temp = key;
          }
        }
        else if ( key == '3') {
          if (temp == key && millis() - t1 < timer) {
            count--; wd[count]++;
            if (wd[count] == 'G') wd[count] = key;
            else if (wd[count] == key) wd[count] = 'D';
          }
          else {
            wd[count] = 'D'; temp = key;
          }
        }
        else if ( key == '4') {
          if (temp == key && millis() - t1 < timer) {
            count--; wd[count]++;
            if (wd[count] == 'J') wd[count] = key;
            else if (wd[count] == key) wd[count] = 'G';
          }
          else {
            wd[count] = 'G'; temp = key;
          }
        }
        else if ( key == '5') {
          if (temp == key && millis() - t1 < timer) {
            count--; wd[count]++;
            if (wd[count] == 'M') wd[count] = key;
            else if (wd[count] == key) wd[count] = 'J';
          }
          else {
            wd[count] = 'J'; temp = key;
          }
        }
        else if ( key == '6') {
          if (temp == key && millis() - t1 < timer) {
            count--; wd[count]++;
            if (wd[count] == 'P') wd[count] = key;
            else if (wd[count] == key) wd[count] = 'M';
          }
          else {
            wd[count] = 'M'; temp = key;
          }
        }
        else if ( key == '7') {
          if (temp == key && millis() - t1 < timer) {
            count--; wd[count]++;
            if (wd[count] == 'T') wd[count] = key;
            else if (wd[count] == key) wd[count] = 'P';
          }
          else {
            wd[count] = 'P'; temp = key;
          }
        }
        else if ( key == '8') {
          if (temp == key && millis() - t1 < timer) {
            count--; wd[count]++;
            if (wd[count] == 'W') wd[count] = key;
            else if (wd[count] == key) wd[count] = 'T';
          }
          else {
            wd[count] = 'T'; temp = key;
          }
        }
        else if ( key == '9') {
          if (temp == key && millis() - t1 < timer) {
            count--; wd[count]++;
            if (wd[count] > 'Z') wd[count] = key;
            else if (wd[count] == key) wd[count] = 'W';
          }
          else {
            wd[count] = 'W'; temp = key;
          }
        }
        else if (key == '0') wd[count] = 32;
        count++;
        t1 = millis();
        display_update();
      }
      break;
    case RELEASED:
      digitalWrite(13, 0);
      break;
    case HOLD:
      digitalWrite(13, 1);
      break;
  }
}
