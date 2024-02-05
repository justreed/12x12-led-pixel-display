#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2
#define COLOR_DEPTH 8
#define SCALE 30 // Adjust for different wave patterns

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];
int jPosition = 0; // Global variable to track the horizontal position of the "J"
CRGBPalette16 currentPalette;

void setup() {
  delay(3000); // Powerup delay
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  currentPalette = RainbowColors_p; // Start with a rainbow color palette
}

void loop() {
  drawBackground();
  drawLetterJ(jPosition);
  FastLED.show();

  // Update the position of the "J"
  jPosition++;
  if (jPosition > WIDTH) jPosition = -6; // Reset position based on the width of your "J"
}

void drawBackground() {
  static uint8_t hue = 0;
  // Fill the noise array based on the current "time"
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      uint8_t noise = inoise8(x * SCALE, y * SCALE, hue);
      leds[XY(x, y)] = ColorFromPalette(currentPalette, noise);
    }
  }
  hue++; // Rapidly increase the hue for faster color transition
}

void drawLetterJ(int jPos) {
  // Parameters for the "J" shape
  int horizontalStart = (WIDTH / 2) - 3 + jPos;
  int horizontalEnd = (WIDTH / 2) + 2 + jPos;
  int verticalStart = HEIGHT - 3;
  int verticalEnd = 0; // Ensure the vertical line goes to the top

  // Top horizontal line of J
  for (int x = horizontalStart; x <= horizontalEnd; x++) {
    if (x >= 0 && x < WIDTH) {
      leds[XY(x, HEIGHT - 2)] = CRGB::White;
    }
  }

  // Vertical line of J
  for (int y = verticalStart; y >= verticalEnd; y--) {
    int x = WIDTH / 2 + jPos;
    if (x >= 0 && x < WIDTH) {
      leds[XY(x, y)] = CRGB::White;
    }
  }

  // Bottom curve of J
  int curveStartX = WIDTH / 2 - 1 + jPos;
  for (int offset = 0; offset < 3; offset++) {
    int x = curveStartX - offset;
    if (x >= 0 && x < WIDTH) {
      leds[XY(x, 0)] = CRGB::White;
      if (offset < 2) {
        leds[XY(x, 1)] = CRGB::White;
      }
    }
  }
}

// Function to convert (x, y) to LED index in a zigzag pattern
int XY(int x, int y) {
  return y % 2 == 0 ? y * WIDTH + x : y * WIDTH + WIDTH - 1 - x;
}
