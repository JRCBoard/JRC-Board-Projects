void motor(int a, int b) {
  if (a > 0) {
    digitalWrite(lmf, 1); digitalWrite(lmb, 0);
  }
  else{
    a = -a;
    digitalWrite(lmf, 0); digitalWrite(lmb, 1);
  }
  if (b > 0) {
    digitalWrite(rmf, 1); digitalWrite(rmb, 0);
  }
  else{
    b = -b;
    digitalWrite(rmf, 0); digitalWrite(rmb, 1);
  }
  ledcWrite(1, a); ledcWrite(0, b);
}
