#include <ESP32Encoder.h>  // https://github.com/madhephaestus/ESP32Encoder.git
#include <BleKeyboard.h>
BleKeyboard bleKeyboard("JRC Board Knob");
#define CLK 25  // CLK ENCODER
#define DT 26   // DT ENCODER
#define SW 16
#define indicator 17

ESP32Encoder encoder;
long volume, oldVolume;
bool present_mode = 0;
const int led[7] = { 13, 05, 23, 18, 14, 19, 15 };

void setup() {
  for (byte i = 0; i < 7; i++) {
    ledcSetup(i, 1000, 8);
    ledcAttachPin(led[i], i);
  }
  pinMode(16, INPUT_PULLUP);
  pinMode(indicator, OUTPUT);
  digitalWrite(indicator, !present_mode);
  encoder.attachHalfQuad(DT, CLK);
  encoder.setCount(0);
  Serial.begin(115200);
  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected()) {
    volume = rotary_input(!present_mode);
    if (oldVolume != volume) {
      if (!present_mode)
        (oldVolume > volume) ? bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN) : bleKeyboard.write(KEY_MEDIA_VOLUME_UP);
      else
        (oldVolume > volume) ? bleKeyboard.write(KEY_UP_ARROW) : bleKeyboard.write(KEY_DOWN_ARROW);
      oldVolume = volume;
      if (!present_mode) led_level(volume);
      Serial.println(volume);
    }

    if (push(SW))
      (present_mode) ? bleKeyboard.write(KEY_PAGE_DOWN) : bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);

  }
}

long rotary_input(bool a) {
  long t = encoder.getCount() * 2;
  if (a) {
    if (t > 100) {
      t = 100;
      encoder.setCount(50);
    }
    else if (t < 0) {
      t = 0;
      encoder.setCount(0);
    }
  }
  return t;
}
