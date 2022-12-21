int sensor, sum, s[6], mid[6] = {1000, 1000, 1000, 1000, 1000, 1000}, base[6] = {32, 16, 8, 4, 2, 1};
void setup() {
  Serial.begin(9600);

}

void loop() {
  analog_value();
}
void reading() {
  sensor = 0; //this is to refresh initial value
  sum = 0;
  for (int i = 0 ; i < 6 ; i++) {
    (i < 2) ? s[i] = analogRead(26 - i) : s[i] = analogRead(37 - i);
    (s[i] > mid[i]) ? s[i] = 1 : s[i] = 0; //conditional statement. this is to convert analog value to digital. if you want to see real analog value, then comment it. but for line follow, you must uncomment it.
    sensor += s[i] * base[i]; //this is to merge all 6 values and imagine them in a single binary number. then i converted it into decimal number to use as final value. better search about base convertion
    sum += s[i]; //finds out total count of sensor
  }
}

void digital_value() {
  reading();
  for (int i = 5 ; i >= 0 ; i--)
    Serial.print(String(s[i]) + " ");
  Serial.println(sensor);
}
void analog_value() {
  for (int i = 5 ; i >= 0 ; i--) {
    (i < 2) ? s[i] = analogRead(26 - i) : s[i] = analogRead(37 - i);
    Serial.print(String(s[i]) + " ");
  }
  Serial.println();
}
