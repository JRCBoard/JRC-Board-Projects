void setup() {
  pinMode(0, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(19, OUTPUT);
  digitalWrite(14, 0);
  digitalWrite(5, 0);
  digitalWrite(19, 0);
  digitalWrite(0, 0);
  digitalWrite(16, 1);
  ledcSetup(0, 1000, 8);
  ledcSetup(1, 1000, 8);
  ledcSetup(2, 1000, 8);
  ledcAttachPin(13, 0);
  ledcAttachPin(23, 1);
  ledcAttachPin(18, 2);
  Serial.begin(9600);


}

void loop() {
  int r = analogRead(4);
  int a =  mapping(r, 25, 1375, 0, 255);
  int b =  mapping(r, 1375, 2725, 0, 255);
  int c =  mapping(r, 2725, 4075, 0, 255);
  ledcWrite(0, a);
  ledcWrite(1, b);
  ledcWrite(2, c);
  Serial.println(String(a) + " " + String(b) + " " + String(c));
}

int mapping(int a, int b, int c, int d, int e) {
  float ratio = (float)(e - d) / (float)(c - b);
  if (a < b) a = b;
  if (a > c) a = c;
  a = (a - b) * ratio;
  return a;
}
