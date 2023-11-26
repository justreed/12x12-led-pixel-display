#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];
unsigned long previousMillis = 0;
const long interval = 5000; // Interval at which to switch patterns (5 seconds)
int displayState = 0;      // 0 for custom pattern

// Define custom patterns for displaying the name "R"
byte customPatterns[5] = {1, 1, 1, 0, 1}; // R

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();
  previousMillis = millis(); // Initialize the timer
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Switch the pattern after 5 seconds
    previousMillis = currentMillis; // Reset the timer
    displayState = (displayState + 1) % 1; // Remove reference to XY
  }

  FastLED.clear(); // Clear the display on each frame

  if (displayState == 0) {
    // Display custom pattern for "R"
    displayCustomPattern();
  }

  FastLED.show();
  delay(100); // Control the speed of animation
}

// Add the custom pattern display function
void displayCustomPattern() {
  for (int j = 0; j < 5; j++) {
    if (customPatterns[j] == 1) {
      int index = j * 2 + 6;
      leds[index] = CRGB::Red; // Assuming red color for the letter
    }
  }
}c:\Users\JustinReed\OneDrive - Beachcliff Technologies\Documents\Arduino\JACKSON-IS-THE-BEST\JACKSON-IS-THE-BEST.ino

// The rest of your code remains the same...
