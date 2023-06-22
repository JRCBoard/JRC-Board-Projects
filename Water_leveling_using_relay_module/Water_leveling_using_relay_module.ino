int Lvl = 34;//Define the Analog pin# on the Arduino for the level sensor signal
int RelayPin = 33;

void setup() {
Serial.begin(115200); // Start the serial communication
pinMode(RelayPin, OUTPUT); // Set RelayPin as an output pin
}

void loop() {
int water_lvl=analogRead(Lvl);
Serial.print("Water level: ");
Serial.println(water_lvl);
if(water_lvl<=1800)
{
  digitalWrite(RelayPin, HIGH);
}
else
{
digitalWrite(RelayPin, LOW);
}
delay(1000);
}
