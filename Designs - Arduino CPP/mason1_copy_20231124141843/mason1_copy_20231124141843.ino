#include <FastLED.h>

#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  drawPotato(); // Function to draw a potato
  FastLED.show();
  delay(100); // Refresh rate in milliseconds
}

void drawPotato() {
  // Clear previous drawings
  FastLED.clear();

  // Draw a potato shape
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      // Simple oval-like shape
      if (((x > 2 && x < 9) && (y > 1 && y < 10)) || 
          ((x > 3 && x < 8) && (y == 2 || y == 9))) {
        leds[XY(x, y)] = CRGB::Brown; // Brown color for the potato
      }
    }
  }
}

int XY(int x, int y) {
  // Function to convert x, y coordinates to LED index
  int XYindex;
  if (y % 2 == 0) {
    XYindex = (y * WIDTH) + x;
  } else {
    XYindex = (y * WIDTH) + (WIDTH - 1 - x);
  }
  return XYindex;
}
