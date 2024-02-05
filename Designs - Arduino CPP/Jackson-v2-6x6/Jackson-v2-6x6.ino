#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];
unsigned long previousMillis = 0;
const long interval = 100; // Interval at which to move the snake (100 milliseconds)
int snakeLength = 1; // Initial length of the snake
int posX = 0, posY = 0; // Starting position of the snake
int direction = 0; // 0: right, 1: down, 2: left, 3: up
int stepsTaken = 0, stepsToTake = 1; // For controlling the spiral movement

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();
  previousMillis = millis(); // Initialize the timer
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Reset the timer
    moveSnake();
    drawSnake();
  }

  FastLED.show();
  delay(200); // Control the speed of animation
}

void moveSnake() {
  // Update snake's position
  switch(direction) {
    case 0: posX++; break;
    case 1: posY++; break;
    case 2: posX--; break;
    case 3: posY--; break;
  }

  // Check if it's time to turn
  stepsTaken++;
  if (stepsTaken == stepsToTake) {
    stepsTaken = 0;
    direction = (direction + 1) % 4; // Change direction

    // Update steps to take based on current direction
    if (direction == 0 || direction == 2) {
      stepsToTake++;
    }
  }

  // Increase snake length periodically
  if (posX == 0 && posY == 0) {
    snakeLength++;
    if (snakeLength > NUM_LEDS) snakeLength = NUM_LEDS; // Limit the length
  }
}

void drawSnake() {
  FastLED.clear();

  // Draw the snake
  int currentX = posX;
  int currentY = posY;
  for (int i = 0; i < snakeLength; i++) {
    if (currentX >= 0 && currentX < WIDTH && currentY >= 0 && currentY < HEIGHT) {
      leds[XY(currentX, currentY)] = CRGB::Green;
    }
    // Move to the next LED in the snake
    if (--currentY < 0) {
      currentY = HEIGHT - 1;
      if (--currentX < 0) {
        currentX = WIDTH - 1;
      }
    }
  }
}

int XY(int x, int y) {
  // Function to map x, y coordinates to LED index
  int XYindex;
  if (y % 2 == 0) {
    XYindex = (y * WIDTH) + x;
  } else {
    XYindex = (y * WIDTH) + (WIDTH - 1 - x);
  }
  return XYindex;
}
