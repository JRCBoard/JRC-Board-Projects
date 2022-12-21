
#include <ESP32Servo.h>

Servo myservo;
int servoPin = 26;      // GPIO pin used to connect the servo control (digital out)
int potPin = 34;        // GPIO pin used to connect the potentiometer (analog in)
int ADC_Max = 4095;     // This is the default ADC max value on the ESP32 (12 bit ADC width);
int val;    // variable to read the value from the analog pin
void setup()
{
  pinMode(32, OUTPUT); pinMode(25, OUTPUT);
  digitalWrite(32, 1); digitalWrite(25, 0);
  // Allow allocation of all timers
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(servoPin, 500, 2400);   // attaches the servo on pin 18 to the servo object
}

void loop() {
  val = analogRead(potPin);            // read the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, ADC_Max, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // set the servo position according to the scaled value
//  delay(200);                          // wait for the servo to get there
}
