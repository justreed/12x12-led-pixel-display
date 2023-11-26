#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];

void setup() {
  delay(3000); // Powerup delay
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
}

int getLEDIndex(int x, int y) {
  // Calculate index for a zigzag layout
  if (y % 2 == 0) {
    // Even rows (0, 2, 4, ...) run from left to right
    return (y * WIDTH) + x;
  } else {
    // Odd rows (1, 3, 5, ...) run from right to left
    return ((y + 1) * WIDTH) - 1 - x;
  }
}

void drawLetterJ() {
  // Clear the matrix
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  // Top horizontal line of J (shortened)
  int horizontalStart = (WIDTH / 2) - 3; // Adjust as needed
  int horizontalEnd = (WIDTH / 2) + 2;   // Adjust as needed
  for (int x = horizontalStart; x <= horizontalEnd; x++) {
    leds[getLEDIndex(x, HEIGHT - 2)] = CRGB::White;
  }

  // Vertical line of J (full length)
  for (int y = HEIGHT - 3; y >= 0; y--) { // Start just below the horizontal bar
    leds[getLEDIndex(WIDTH / 2, y)] = CRGB::White;
  }

  // Bottom curve of J (widened)
  leds[getLEDIndex(WIDTH / 2 - 1, 0)] = CRGB::White;
  leds[getLEDIndex(WIDTH / 2 - 2, 0)] = CRGB::White;
  leds[getLEDIndex(WIDTH / 2 - 3, 0)] = CRGB::White; // Extend the hook wider
  leds[getLEDIndex(WIDTH / 2 - 2, 1)] = CRGB::White;
  leds[getLEDIndex(WIDTH / 2 - 3, 1)] = CRGB::White; // Extend the hook wider
}

void loop() {
  drawLetterJ();
  FastLED.show();
  delay(5000); // Display the letter J for 5 seconds
  
  // Clear the matrix
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
  FastLED.show();
  delay(1000); // Wait for 1 second before redrawing
}
