void motor(int a, int b) {
  if (a > 0) {
    digitalWrite(lmf, 1);
    digitalWrite(lmb, 0);
  }
  else if (a < 0) {
    a = -a;
    digitalWrite(lmf, 0);
    digitalWrite(lmb, 1);
  }
  else {
    digitalWrite(lmf, 0);
    digitalWrite(lmb, 0);
  }
  
  if (b > 0) {
    digitalWrite(rmf, 1);
    digitalWrite(rmb, 0);
  }
  else if (b < 0) {
    b = -b;
    digitalWrite(rmf, 0);
    digitalWrite(rmb, 1);
  }
  else {
    digitalWrite(rmf, 0);
    digitalWrite(rmb, 0);
  }
  
  ledcWrite(0, a);
  ledcWrite(1, b);
}
