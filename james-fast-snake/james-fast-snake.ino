#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2
#define SNAKE_LENGTH 15

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];
int snakePos[SNAKE_LENGTH][2]; // Stores the position of each segment of the snake
int headIndex = 0; // Index of the snake's head in the snakePos array

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();
  initializeSnake();
}

void loop() {
  moveSnake();
  drawSnake();
  FastLED.show();
  delay(0); // Adjust for speed
}

void initializeSnake() {
  // Initialize the snake position, starting at the bottom left
  for (int i = 0; i < SNAKE_LENGTH; i++) {
    snakePos[i][0] = 0; // X position
    snakePos[i][1] = -i; // Y position, starts off the screen
  }
}

void moveSnake() {
  // Move the snake's head
  int nextX = snakePos[headIndex][0];
  int nextY = snakePos[headIndex][1] + 1;

  // Check for edge of display and zigzag pattern
  if (nextY >= HEIGHT) {
    nextY = 0;
    nextX += 1;
    if (nextX >= WIDTH) {
      nextX = 0;
    }
  }

  // Update the head position
  headIndex = (headIndex + 1) % SNAKE_LENGTH;
  snakePos[headIndex][0] = nextX;
  snakePos[headIndex][1] = nextY;
}

void drawSnake() {
  FastLED.clear();
  for (int i = 0; i < SNAKE_LENGTH; i++) {
    int x = snakePos[i][0];
    int y = snakePos[i][1];
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
      leds[XY(x, y)] = CHSV((i * 8) % 256, 255, 255); // Color changes along the snake's length
    }
  }
}

int XY(int x, int y) {
  // Zigzag pattern layout
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

// Additional functions or logic as needed
