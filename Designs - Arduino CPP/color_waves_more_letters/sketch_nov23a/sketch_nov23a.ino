#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];

// Smiley Face Patterns
const byte smileyHappy[12][12] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const byte smileyNeutral[12][12] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  animateSmileyFace();
  FastLED.show();
  delay(500); // Adjust the speed of the smiley face's expression change
}

void animateSmileyFace() {
    static bool isHappy = true;
    isHappy = !isHappy; // Toggle between happy and neutral face

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (isHappy) {
                if (smileyHappy[y][x] == 1) {
                    leds[XY(x, y)] = CRGB::Yellow;
                }
            } else {
                if (smileyNeutral[y][x] == 1) {
                    leds[XY(x, y)] = CRGB::Yellow;
                }
            }
        }
    }

    FastLED.clear(); // Clear the display on each frame
}

int XY(int x, int y) {
  int XYindex;
  if (y % 2 == 0) {
    XYindex = (y * WIDTH) + x;
  } else {
    XYindex = (y * WIDTH) + (WIDTH - 1 - x);
  }
  return XYindex;
}
