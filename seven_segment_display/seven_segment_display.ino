#define A 15
#define B 14
#define C 13
#define D 05
#define E 23
#define F 18
#define G 19

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
}

void loop() {
  display(0); delay(1000);
  display(1); delay(1000);
  display(2); delay(1000);
  display(3); delay(1000);
  display(4); delay(1000);
  display(5); delay(1000);
  display(6); delay(1000);
  display(7); delay(1000);
  display(8); delay(1000);
  display(9); delay(1000);
}

void display(int num) {
  (num != 1 && num != 4) ? digitalWrite(A, HIGH) : digitalWrite(A, LOW);
  (num != 5 && num != 6) ? digitalWrite(B, HIGH) : digitalWrite(B, LOW);
  (num != 2) ? digitalWrite(C, HIGH) : digitalWrite(C, LOW);
  (num != 1 && num != 4 && num != 7) ? digitalWrite(D, HIGH) : digitalWrite(D, LOW);
  (num == 0 || num == 2 || num == 6 || num == 8) ? digitalWrite(E, HIGH) : digitalWrite(E, LOW);
  (num != 1 && num != 2 && num != 3 && num != 7) ? digitalWrite(F, HIGH) : digitalWrite(F, LOW);
  (num != 0 && num != 1 && num != 7) ? digitalWrite(G, HIGH) : digitalWrite(G, LOW);
}
