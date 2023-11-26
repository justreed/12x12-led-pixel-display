#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];

int ballX = WIDTH / 2;
int ballY = HEIGHT / 2;
int ballDirX = 1; // Ball movement direction in X
int ballDirY = 1; // Ball movement direction in Y

int leftPaddleY = HEIGHT / 2;
int rightPaddleY = HEIGHT / 2;
int paddleHeight = 2; // Height of the paddles

int leftPaddleDir = 1; // Direction of left paddle movement
int rightPaddleDir = -1; // Direction of right paddle movement

int leftScore = 0; // Score for left player
int rightScore = 0; // Score for right player
const int winningScore = 5; // Score required to win the game

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  moveBall();
  movePaddles();
  checkWinCondition();
  drawGame();
  FastLED.show();
  delay(100); // Control the speed of the game
}

void moveBall() {
  // Update ball position
  ballX += ballDirX;
  ballY += ballDirY;

  // Check for collisions with top and bottom walls
  if (ballY <= 0 || ballY >= HEIGHT - 1) {
    ballDirY *= -1; // Reverse Y direction
  }

  // Check for collisions with paddles
  if ((ballX == 1 && ballY >= leftPaddleY && ballY < leftPaddleY + paddleHeight) ||
      (ballX == WIDTH - 2 && ballY >= rightPaddleY && ballY < rightPaddleY + paddleHeight)) {
    ballDirX *= -1; // Reverse X direction
  }

  // Check for scoring
  if (ballX <= 0) {
    rightScore++;
    resetBallAndPaddles();
  } else if (ballX >= WIDTH - 1) {
    leftScore++;
    resetBallAndPaddles();
  }
}

void movePaddles() {
  // Move left paddle
  leftPaddleY += leftPaddleDir;
  if (leftPaddleY <= 0 || leftPaddleY >= HEIGHT - paddleHeight) {
    leftPaddleDir *= -1; // Change direction if it hits top or bottom
  }

  // Move right paddle
  rightPaddleY += rightPaddleDir;
  if (rightPaddleY <= 0 || rightPaddleY >= HEIGHT - paddleHeight) {
    rightPaddleDir *= -1; // Change direction if it hits top or bottom
  }
}

void checkWinCondition() {
  if (leftScore >= winningScore || rightScore >= winningScore) {
    leftScore = 0;
    rightScore = 0;
    resetBallAndPaddles(); // Reset the game
  }
}

void drawGame() {
  FastLED.clear();

  // Draw ball
  leds[XY(ballX, ballY)] = CRGB::White;

  // Draw left paddle
  for (int i = 0; i < paddleHeight; i++) {
    leds[XY(0, leftPaddleY + i)] = CRGB::Red;
  }

  // Draw right paddle
  for (int i = 0; i < paddleHeight; i++) {
    leds[XY(WIDTH - 1, rightPaddleY + i)] = CRGB::Blue;
  }

  // Draw scores
  drawScores();
}

void drawScores() {
  // Left score
  for (int i = 0; i < leftScore && i < WIDTH / 2; i++) {
    leds[XY(i, HEIGHT - 1)] = CRGB::Red;
  }

  // Right score
  for (int i = 0; i < rightScore && i < WIDTH / 2; i++) {
    leds[XY(WIDTH - 1 - i, HEIGHT - 1)] = CRGB::Blue;
  }
}

void resetBallAndPaddles() {
  ballX = WIDTH / 2;
  ballY = HEIGHT / 2;
  ballDirX = random(2) * 2 - 1;
  ballDirY = random(2) * 2 - 1;
  leftPaddleY = HEIGHT / 2;
  rightPaddleY = HEIGHT / 2;
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
