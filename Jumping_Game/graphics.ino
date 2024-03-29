void initializeGraphics() {
  static byte graphics[] = {
    // Run position 1
    0x0C, 0x0C, 0x00, 0x0E, 0x1C, 0x0C, 0x1A, 0x13,
    // Run position 2
    0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0E,
    // Jump
    0x0C, 0x0C, 0x00, 0x1E, 0x0D, 0x1F, 0x10, 0x00,
    // Jump lower
    0x1E, 0x0D, 0x1F, 0x10, 0x00, 0x00, 0x00, 0x00,
    // Ground
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
    // Ground right
    0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    // Ground left
    0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
  };
  int i;
  // Skip using character 0, this allows lcd.print() to be used to
  // quickly draw multiple characters
  for (i = 0; i < 7; ++i) {
    lcd.createChar(i + 1, &graphics[i * 8]);
  }
  for (i = 0; i < TERRAIN_WIDTH; ++i) {
    terrainUpper[i] = SPRITE_TERRAIN_EMPTY;
    terrainLower[i] = SPRITE_TERRAIN_EMPTY;
  }
}
