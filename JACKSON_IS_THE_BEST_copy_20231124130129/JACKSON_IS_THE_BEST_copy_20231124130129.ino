#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];

// Eye position and state
int eyePosition = 3; // Starting horizontal position of the eyes
unsigned long lastUpdate = 0; // Time of the last eye movement
const int eyeMoveInterval = 1000; // Time in milliseconds between eye movements

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  unsigned long currentMillis = millis();

  // Update eye position at specified intervals
  if (currentMillis - lastUpdate > eyeMoveInterval) {
    lastUpdate = currentMillis;
    animateEmoji();
  }

  FastLED.show();
}

void animateEmoji() {
  FastLED.clear(); // Clear the display on each frame

  // Draw Emoji Face
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      leds[XY(x, y)] = CRGB::Yellow;
    }
  }

  // Draw Mouth (now on the top)
  for (int x = 4; x <= 7; x++) {
    leds[XY(x, 3)] = CRGB::Black; // Mouth at the top
  }

  // Update Eye Position (at the bottom)
  drawSquareEye(eyePosition, HEIGHT - 5); // Left eye
  drawSquareEye(eyePosition + 3, HEIGHT - 5); // Right eye

  // Shift eyes from side to side
  eyePosition++;
  if (eyePosition > 4) {
    eyePosition = 3;
  }
}

void drawSquareEye(int x, int y) {
  leds[XY(x, y)] = CRGB::Black;
  leds[XY(x+1, y)] = CRGB::Black;
  leds[XY(x, y+1)] = CRGB::Black;
  leds[XY(x+1, y+1)] = CRGB::Black;
}

int XY(int x, int y) {
  // Mapping function for LED matrix
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
