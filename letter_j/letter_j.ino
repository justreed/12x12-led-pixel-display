#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2
#define COLOR_DEPTH 8
#define SCALE 30 // Adjust this for different wave patterns

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];

// Define a color palette
CRGBPalette16 currentPalette;

void setup() {
  delay(3000); // Powerup delay
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  currentPalette = RainbowColors_p; // Start with a rainbow color palette
}

void loop() {
  static uint8_t hue = 0;
  // Fill the noise array based on the current "time"
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      uint8_t noise = inoise8(x * SCALE, y * SCALE, hue);
      leds[XY(x, y)] = ColorFromPalette(currentPalette, noise);
    }
  }
  FastLED.show();
  hue++; // Slowly increase the hue for color transition
  delay(1); // Adjust for speed
}

// Function to convert (x, y) to LED index in a zigzag pattern
int XY(int x, int y) {
  return y % 2 == 0 ? y * WIDTH + x : y * WIDTH + WIDTH - 1 - x;
}
