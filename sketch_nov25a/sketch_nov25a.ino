#include <MatrixDisplay.h>

MatrixDisplay display;

void setup() {
  // Initialize the matrix display
  display.begin();
}

void loop() {
  // Clear the display
  display.clear();

  // Define the Christmas tree pattern
  int tree[12][12] = {
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  // Draw the Christmas tree
  for (int y = 0; y < 12; y++) {
    for (int x = 0; x < 12; x++) {
      if (tree[y][x] == 1) {
        display.drawPixel(x, y, HIGH);
      }
    }
  }

  // Update the display
  display.show();

  // Keep the pattern displayed
  delay(1000);
}
