#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];

// Pac-Man position and direction
int pacmanX = 0;
int pacmanDirection = 1; // 1 for right, -1 for left

// Pac-Man patterns
const byte pacmanOpen[12][12] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

const byte pacmanClosed[12][12] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  animatePacman();
  FastLED.show();
  delay(100); // Control the speed of animation
}

void animatePacman() {
    static bool mouthOpen = true;
    static unsigned long lastMove = millis();

    FastLED.clear(); // Clear the display on each frame

    // Draw Pac-Man
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (mouthOpen) {
                if (pacmanOpen[y][x] == 1) {
                    leds[XY(pacmanX + x, y)] = CRGB::Yellow;
                }
            } else {
                if (pacmanClosed[y][x] == 1) {
                    leds[XY(pacmanX + x, y)] = CRGB::Yellow;
                }
            }
        }
    }

    // Animate Pac-Man
    if (millis() - lastMove > 500) { // Adjust timing as needed
        lastMove = millis();
        mouthOpen = !mouthOpen; // Toggle mouth state
        pacmanX += pacmanDirection;

        // Change direction at edges
        if (pacmanX <= 0 || pacmanX >= WIDTH - 12) {
            pacmanDirection *= -1;
        }
    }
}

int XY(int x, int y) {
  // Modify this function if your LED matrix starts at the lower-left corner
  // and ensure it accounts for the layout (zigzag or straight)
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
