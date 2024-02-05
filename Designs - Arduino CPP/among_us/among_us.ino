#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2
#define NUM_LEDS WIDTH * HEIGHT

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(100); // Adjust brightness as needed
}

void loop() {
  drawAmongUsCharacter();
  FastLED.show();
  delay(2000); // Delay to keep the character displayed
}

void drawAmongUsCharacter() {
  // Set the background to white
  fill_solid(leds, NUM_LEDS, CRGB::White);

  // Among Us character design with black outline and detailed visor
  // 0 for white (background), 1 for black (outline), 2 for red (body), 3 for blue (visor), 4 for white (visor highlight)
  byte amongUsCharacter[12][12] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 2, 2, 1, 2, 2, 1, 1, 1, 1},
    {1, 1, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1},
    {1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1},
    {1, 2, 2, 2, 2, 3, 3, 3, 3, 2, 2, 1},
    {1, 1, 2, 2, 2, 3, 3, 4, 4, 2, 1, 1},
    {1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  };

  // Draw the Among Us character
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      switch (amongUsCharacter[y][x]) {
        case 1:
          leds[XY(x, y)] = CRGB::Black; // Outline
          break;
        case 2:
          leds[XY(x, y)] = CRGB::Red; // Body
          break;
        case 3:
          leds[XY(x, y)] = CRGB::Blue; // Visor
          break;
        case 4:
          leds[XY(x, y)] = CRGB::White; // Visor highlight
          break;
      }
    }
  }
}

int XY(int x, int y) {
  // Mapping function for 2D coordinates to 1D LED index
  int XYindex;
  if (y % 2 == 0) {
    XYindex = (y * WIDTH) + x;
  } else {
    XYindex = (y * WIDTH) + (WIDTH - 1 - x);
  }
  return XYindex;
}
