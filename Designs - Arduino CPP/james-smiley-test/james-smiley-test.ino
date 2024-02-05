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
  // Expand squares in the interior
  for (int i = 1; i <= (HEIGHT / 2) - 2; i++) {
    drawInteriorSquare(i, true);
    FastLED.show();
    delay(300); // Delay between expanding squares
  }

  // Shrink squares in the interior
  for (int i = (HEIGHT / 2) - 3; i >= 1; i--) {
    drawInteriorSquare(i, false);
    FastLED.show();
    delay(300); // Delay between shrinking squares
  }
}

void drawInteriorSquare(int size, bool state) {
  int minIndex = HEIGHT / 2 - size;
  int maxIndex = HEIGHT / 2 + size;

  // Ensure the square is drawn inside the border, excluding outer rows and columns
  minIndex = max(2, minIndex);
  maxIndex = min(HEIGHT - 3, maxIndex);

  for (int y = minIndex; y <= maxIndex; y++) {
    for (int x = minIndex; x <= maxIndex; x++) {
      leds[XY(x, y)] = state ? getRainbowColor(y) : CRGB::Black;
    }
  }
}

CRGB getRainbowColor(int y) {
    switch (y / (HEIGHT / 7)) {
        case 0: return CRGB::Red;
        case 1: return CRGB::Orange;
        case 2: return CRGB::Yellow;
        case 3: return CRGB::Green;
        case 4: return CRGB::Blue;
        case 5: return CRGB::Indigo;
        default: return CRGB::Violet;
    }
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
