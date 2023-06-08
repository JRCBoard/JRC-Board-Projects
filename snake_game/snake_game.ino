#include <EEPROM.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);

int sw[4] = { 14, 02, 05, 23 }, buzzer = 19;  //right, down, left, up
short int pos[400] = { 600, 400, 200, 000 };
short int foodx, foody, dir = 3, len = 4, dl = 100;
bool eat = 1, s_b = 0;
uint32_t m81, m82, m83;
String value;
byte beep = 30;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setRotation(2);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  for (byte i = 0; i < 4; i++) pinMode(sw[i], INPUT_PULLUP);
  //  while (1) Serial.println(String(digitalRead(sw[0])) + String(digitalRead(sw[1])) + String(digitalRead(sw[2])) + String(digitalRead(sw[3])));
  snake_game();
}

void loop() {
  // put your main code here, to run repeatedly:
}
