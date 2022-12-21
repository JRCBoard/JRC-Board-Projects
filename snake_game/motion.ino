void motion() {
  int posx = pos[0] / 100;
  int posy = pos[0] % 100;
  for (int i = len ; i > 0; i--) pos[i] = pos[i - 1];
  if (dir == 1) posx -= 2;
  else if (dir == 3) posx += 2;
  else if (dir == 2) posy -= 2;
  else if (dir == 4) posy += 2;
  if (posx > 40) posx = 0;
  else if (posx < 0) posx = 40;
  if (posy > 20) posy = 0;
  else if (posy < 0) posy = 20;

  pos[0] = posx * 100 + posy;
  if (pos[0] == 100 * foodx + foody) {
    eat = 1; len++;
  }
}
