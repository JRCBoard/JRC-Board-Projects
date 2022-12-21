#include <ESP32Servo.h>
Servo myservo;
#define triggerPin 15
#define echoPin 16
int distance;
unsigned long m1, m2;
void setup() {
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(17, 500, 2400);
  myservo.write(0);

  Serial.begin(9600);
}

void loop() {
  // Pass INC as a parameter to get the distance in inches
  distance = read_distance();
  Serial.println(distance);
  if (distance > 0 && distance < 10) {
    for (int i = 0; i <= 90; i++) {
      myservo.write(i); delay(10);
    }
a:   m1 = m2 = millis();
    while (m2 - m1 < 1000) {
      m2 = millis();
      distance = read_distance();
      Serial.println(distance);
      if (distance > 2 && distance < 10) m1 = m2;
    }
    for (int i = 90; i >= 0; i--) {
      myservo.write(i);
      distance = read_distance();
      Serial.println(distance);
      if (distance > 0 && distance < 10) {
        while (i < 90) {
          myservo.write(i); delay(10); i++;
        }
        goto a;
      }
    }
  }
}


long read_distance()
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  int x = pulseIn(echoPin, HIGH);
  x = 0.01723 * x;
  return x;
}
