void food() {
  eat = 0;
f:  foodx = (rand() % 20) * 2;
  foody = (rand() % 10) * 2;
  for (short int i = 0; i < len ; i ++) if (pos[i] == 100 * foodx + foody) goto f;
}
