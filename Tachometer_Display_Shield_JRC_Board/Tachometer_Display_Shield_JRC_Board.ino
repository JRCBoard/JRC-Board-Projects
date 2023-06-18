#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
SSD1306AsciiWire oled;
#define _TIMERINTERRUPT_LOGLEVEL_ 0
#include "ESP32TimerInterrupt.h"
#define TIMER0_INTERVAL_MS 1
#define DEBOUNCING_INTERVAL_MS 50
#define LOCAL_DEBUG 0
ESP32Timer ITimer0(0);

unsigned int SWPin = 19;
volatile unsigned long rotationTime = 0;
volatile int debounceCounter;

int RPM = 0;
int avgRPM = 0;
int maxRPM = 0;

bool IRAM_ATTR TimerHandler0(void* timerNo) {
  if (!digitalRead(SWPin) && (debounceCounter >= DEBOUNCING_INTERVAL_MS / TIMER0_INTERVAL_MS)) {
    RPM = (6000000 / (rotationTime * TIMER0_INTERVAL_MS));
    avgRPM = (2 * avgRPM + RPM) / 3;
    if(avgRPM > maxRPM) maxRPM = avgRPM;
    rotationTime = 0;
    debounceCounter = 0;
  }

  else debounceCounter++;

  if (rotationTime >= 1000) {
    RPM = 0;
    avgRPM = (avgRPM + 3 * RPM) / 4;
    rotationTime = 0;
  }

  else rotationTime++;

  return true;
}

void setup() {
  pinMode(SWPin, INPUT_PULLUP);
  Wire.begin();
  Wire.setClock(400000L);
  oled.begin(&Adafruit128x64, 0x3C);
  oled.setFont(System5x7);
  oled.set2X();
  Serial.begin(115200);
  ITimer0.attachInterruptInterval(TIMER0_INTERVAL_MS * 1000, TimerHandler0);
}

void loop() {
  if (avgRPM > 0) display();
  else max_display();
  delay(1000);
}

void text(String t, byte x, byte y) {
  oled.setCursor(x, y);
  oled.print(t);
}

void display(){
  oled.clear();
  text("RPM: " + String(RPM / 100) + "     ",0,0);
  text("AVG: " + String(avgRPM / 100) + "     ",0,3);
  text("MAX: " + String(maxRPM / 100) + "     ",0,6);
}

void max_display(){
  oled.clear();
  text("TACOMETER",10,1);
  text("MAX: " + String(maxRPM / 100),0,5);
}
