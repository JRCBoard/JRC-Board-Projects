int latchPin = 4;
int clockPin = 15;
int dataPin = 14;
byte data1 = 0b11111111;
byte data2 = 0b11111111;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(latchPin, 0);
  digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 0);
  shiftOut(data2);
  shiftOut(data1);
  Serial.begin(9600);
}

void loop() {
}

void shiftOut(byte myDataOut) {
  int i = 0;
  int pinState;
  for (i = 7; i >= 0; i--)   {
    digitalWrite(clockPin, 0);
    digitalWrite(latchPin, 0);
    if ( myDataOut & (1 << i) ) pinState = 1;
    else pinState = 0;
    digitalWrite(dataPin, pinState);
    delayMicroseconds(10);
    digitalWrite(clockPin, 1);
    delayMicroseconds(10);
    digitalWrite(clockPin, 0);
    digitalWrite(dataPin, 0);
    digitalWrite(latchPin, 1);
    delayMicroseconds(10);
    digitalWrite(latchPin, 0);
  }
  digitalWrite(clockPin, 0);
  digitalWrite(latchPin, 0);
}
