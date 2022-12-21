void draw() {
  for (short i = 0; i < len; i++) display.fillRect((pos[i] / 100) * 3, (pos[i] % 100) * 3, 3, 3, WHITE);
  for (short i = 0; i < len - 1; i++)
    if ((pos[i + 1] / 100) - (pos[i] / 100) <= 2 && (pos[i + 1] / 100) - (pos[i] / 100) >= -2 && (pos[i + 1] % 100) - (pos[i] % 100) <= 2 && (pos[i + 1] % 100) - (pos[i] % 100) >= -2)
      display.fillRect(((pos[i] / 100) + ((pos[i + 1] / 100) - (pos[i] / 100)) / 2) * 3, ((pos[i] % 100) + ((pos[i + 1] % 100) - (pos[i] % 100)) / 2) * 3, 3, 3, WHITE);
  display.fillRect(foodx * 3, foody * 3, 3, 3, WHITE);
  display.display(); display.clearDisplay();
}

void text(String t, byte x, byte y) {
  display.setCursor(x, y);
  display.print(t);
}
