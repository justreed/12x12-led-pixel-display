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
  drawSwirlingRainbow();
  FastLED.show();
  delay(100);
}

int XY(int x, int y) {
  // Function to convert (x,y) to index for a zigzag layout
  int XYindex;
  if (y % 2 == 0) {
    // Even rows run forwards
    XYindex = (y * WIDTH) + x;
  } else {
    // Odd rows run backwards
    XYindex = (y * WIDTH) + (WIDTH - 1 - x);
  }
  return XYindex;
}

void drawSwirlingRainbow() {
  static uint8_t hue = 0; // Starting hue
  static int swirlPosition = 0; // Position of the swirl
  static float radius = 0; // Radius of the swirl

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      // Calculate distance from the center
      float dx = x - WIDTH / 2;
      float dy = y - HEIGHT / 2;
      float distance = sqrt(dx * dx + dy * dy);

      // Check if the pixel is within the swirling radius
      if (distance <= radius) {
        // Calculate the hue offset based on swirl position and distance
        int hueOffset = (int)(distance + swirlPosition) % WIDTH;
        leds[XY(x, y)] = CHSV(hue + hueOffset * (256 / WIDTH), 255, 255);
      }
    }
  }

  hue++; // Increment the hue for the next frame
  swirlPosition = (swirlPosition + 1) % (WIDTH / 2); // Move the swirl position
  radius = fmod(radius + 0.5, WIDTH / 2); // Increase the radius and wrap around
}
