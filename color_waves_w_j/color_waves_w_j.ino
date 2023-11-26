#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];
unsigned long previousMillis = 0;
const long interval = 5000; // Interval at which to switch images (5 seconds)
int displayState = 0; // 0 for snowflake, 1 for Christmas tree, 2 for Santa's sleigh
// Global variables for snowflake position and drift direction
int snowflakeX = WIDTH / 2;
int snowflakeY = -10; // Start above the matrix
int driftDirection = 1; // 1 for right, -1 for left


void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.clear();
  FastLED.show();
  previousMillis = millis(); // Initialize the timer
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Switch the image after 5 seconds
    previousMillis = currentMillis; // Reset the timer
    displayState = (displayState + 1) % 3; // Increment and wrap the state
  }

  FastLED.clear(); // Clear the display on each frame
  
  if (displayState == 0) {
    // Run snowflake animation
    moveSnowflake();
    drawSnowflake();
  } else if (displayState == 1) {
    // Display Christmas tree
    drawChristmasTree();
  } else if (displayState == 2) {
    // Display Santa
    drawSantaClausHead();

  }

  FastLED.show();
  delay(100); // Control the speed of animation
}

void drawSantaClausHead() {
    FastLED.clear();
    
    // Drawing the hat
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (y < 2 || (x > 3 && x < 8)) { // Red part of the hat
                leds[XY(x, y)] = CRGB::Red;
            } else { // White trim of the hat
                leds[XY(x, y)] = CRGB::White;
            }
        }
    }

    // Drawing the face
    for (int y = 3; y < 6; y++) {
        for (int x = 4; x < 8; x++) {
            leds[XY(x, y)] = CRGB::Orange; // Assuming orange for face, change as needed
        }
    }

    // Drawing the beard
    for (int y = 6; y < HEIGHT; y++) {
        for (int x = 2; x < 10; x++) {
            leds[XY(x, y)] = CRGB::White;
        }
    }

    // Adding eyes
    leds[XY(5, 4)] = CRGB::Black;
    leds[XY(6, 4)] = CRGB::Black;

    FastLED.show();
}


void drawChristmasTree() {
  FastLED.clear();

  // Draw the tree
  for (int y = 0; y < HEIGHT; y++) {
    int treeWidth = y / 2; // Tree width increases as we go down
    for (int x = WIDTH / 2 - treeWidth; x <= WIDTH / 2 + treeWidth; x++) {
      leds[XY(x, HEIGHT - y - 1)] = CRGB::Green; // Draw tree leaves
    }
  }

  // Draw the stump
  for (int y = 0; y < 2; y++) {
    for (int x = WIDTH / 2 - 1; x <= WIDTH / 2; x++) {
      leds[XY(x, y)] = CRGB::Brown; // Draw stump
    }
  }

  // Add twinkling lights
  CRGB colors[] = {CRGB::Yellow, CRGB::Orange, CRGB::Blue, CRGB::Red};
  for (int i = 0; i < 20; i++) {
    int lightX = random(WIDTH);
    int lightY = random(HEIGHT);
    if (leds[XY(lightX, lightY)] == CRGB::Green) {
      leds[XY(lightX, lightY)] = colors[random(4)];
    }
  }

  FastLED.show();
}



// Functions to handle the snowflake animation (moveSnowflake, drawSnowflake, etc.) are not displayed for brevity

int XY(int x, int y) {
  // Modify this function if your LED matrix starts at the lower-left corner
  // and
  // ... and ensure it accounts for the layout (zigzag or straight)
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


void drawSnowflake() {
  // Define the snowflake pattern based on the provided structure.
  byte snowflakePattern[10][10] = {
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 0},
    {0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {0, 1, 1, 1, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 0, 1, 0}
  };

  for (int dx = 0; dx < 10; dx++) {
    for (int dy = 0; dy < 10; dy++) {
      int posX = snowflakeX + dx - 5; // Adjust for snowflake width
      int posY = snowflakeY + dy - 5; // Adjust for snowflake height
      if (posX >= 0 && posX < WIDTH && posY >= 0 && posY < HEIGHT) {
        if (snowflakePattern[dy][dx] == 1) {
          leds[XY(posX, posY)] = CRGB::White;
        }
      }
    }
  }

  FastLED.show();
}


void moveSnowflake() {
  static unsigned long lastMove = millis();
  if (millis() - lastMove > 300) { // Slow down the snowflake's descent
    lastMove = millis();

    snowflakeY--; // Move the snowflake downwards
    if (snowflakeY < 0) {
      resetSnowflake();
    }

    // Horizontal drift
    snowflakeX += driftDirection;
    if (snowflakeX <= 0 || snowflakeX >= WIDTH - 1) {
      driftDirection *= -1; // Change direction at the edges
    }
  }
}

void resetSnowflake() {
  snowflakeX = random(WIDTH);
  snowflakeY = HEIGHT - 1; // Start from the bottom of the display
  driftDirection = random(2) * 2 - 1; // Random drift direction
}
