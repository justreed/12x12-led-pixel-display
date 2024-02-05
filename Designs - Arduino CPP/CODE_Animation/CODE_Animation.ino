#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2
#define NUM_LEDS WIDTH * HEIGHT

CRGB leds[NUM_LEDS];

int letterX, letterY;
int moveX, moveY;
int letterIndex = 0; // 0 for C, 1 for O, 2 for D, 3 for E
unsigned long previousMillis = 0;
const long interval = 15000; // Slower interval for changing letters (15 seconds)

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  initializeLetterPosition();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= INTERVAL_CHANGE_LETTER) {
    previousMillis = currentMillis;
    letterIndex = (letterIndex + 1) % 4; // Move to next letter
    initializeLetterPosition(); // Randomize position for next letter
  }

  moveLetters();
  drawMatrixBackground(); // Draw the green streaks background
  drawLetter(letterIndex); // Draw the moving letter
  FastLED.show();
  delay(100);
}

void moveLetters() {
  static unsigned long lastMoveTime = 0;
  unsigned long currentMillis = millis();

  // Update position every 1000 milliseconds (slowed down by 50%)
  if (currentMillis - lastMoveTime > 1000) {
    lastMoveTime = currentMillis;

    // Slower movement logic
    moveX = (random(2) * 2 - 1) / 2; // -0.5, 0, or 0.5
    moveY = (random(2) * 2 - 1) / 2; // -0.5, 0, or 0.5

    letterX = (letterX + moveX + WIDTH) % WIDTH;
    letterY = (letterY + moveY + HEIGHT) % HEIGHT;
  }
}

void initializeLetterPosition() {
  letterX = random(WIDTH - 6); // Adjust for thicker letters
  letterY = random(HEIGHT - 8); // Adjust for height of thicker letters
  moveX = random(2) * 2 - 1; // Original movement speed
  moveY = random(2) * 2 - 1;
}

void updateLetterPosition() {
  letterX += moveX;
  letterY += moveY;

  // Adjust bounds for thicker letters
  if (letterX <= 0 || letterX >= WIDTH - 6) moveX = -moveX;
  if (letterY <= 0 || letterY >= HEIGHT - 8) moveY = -moveY;
}

void drawBackground(int index) {
  CRGB bgColor = (index % 2 == 0) ? CRGB::Blue : CRGB::Green;
  bgColor.fadeToBlackBy(64); // Dimming by 25%
  fill_solid(leds, NUM_LEDS, bgColor);
}

void drawMatrixBackground() {
  static byte streaks[WIDTH] = {0};

  // Update streaks
  for (int x = 0; x < WIDTH; x++) {
    if (streaks[x] > 0) {
      streaks[x]--; // Fade out streak
    } else if (random(10) == 0) {
      streaks[x] = HEIGHT - 1; // Start a new streak
    }
  }

  // Draw background with streaks
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      if (streaks[x] > y) {
        leds[XY(x, y)] = CRGB::Green;
      } else {
        leds[XY(x, y)] = CRGB::Black;
      }
    }
  }
}


CRGB getRandomColor() {
  return CRGB(random(255), random(255), random(255)).fadeToBlackBy(64); // Dimmed by 25%
}


void drawLetter(int index) {
  switch (index) {
    case 0: drawC(); break;
    case 1: drawO(); break;
    case 2: drawD(); break;
    case 3: drawE(); break;
  }
}

void drawO() {
  byte letterO[12][12] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  drawLetterFromArray(letterO, letterX, letterY);
}


void drawC() {
  byte letterC[12][12] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

   drawLetterFromArray(letterC, letterX, letterY);
}
void drawD() {
  byte letterD[12][12] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  drawLetterFromArray(letterD, letterX, letterY);
}


void drawE() {
  byte letterE[12][12] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  };

  drawLetterFromArray(letterE, letterX, letterY);
}

void drawLetterFromArray(byte letter[12][12], int posX, int posY) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      int wrappedX = (x + posX) % WIDTH;
      int wrappedY = (y + posY) % HEIGHT;
      if (letter[y][x] == 1) {
        leds[XY(wrappedX, wrappedY)] = getBoldColor();
      }
    }
  }
}
CRGB getBoldColor() {
  // Ensure at least one of the RGB components is set to a high value
  int highValue = random(192, 256); // 192 to 255
  int lowValue1 = random(0, 128);   // 0 to 127
  int lowValue2 = random(0, 128);   // 0 to 127

  switch (random(3)) {
    case 0: return CRGB(highValue, lowValue1, lowValue2); // Red dominant
    case 1: return CRGB(lowValue1, highValue, lowValue2); // Green dominant
    case 2: return CRGB(lowValue1, lowValue2, highValue); // Blue dominant
  }

  return CRGB::Black; // Fallback, should not occur
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
