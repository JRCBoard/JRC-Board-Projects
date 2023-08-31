void motor(int a, int b) {
  if (a > 0) motor3(1, a);
  else if (a < 0) motor3(0, -a);
  else motor3_stop();
  if (b > 0) motor1(1, b);
  else if (b < 0) motor1(0, -b);
  else motor1_stop();
}
