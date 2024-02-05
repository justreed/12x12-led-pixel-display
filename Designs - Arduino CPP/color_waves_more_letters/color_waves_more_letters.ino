#include <FastLED.h>
#define WIDTH 12
#define HEIGHT 12
#define LED_PIN 2
#define COLOR_DEPTH 8
#define SCALE 30

const int NUM_LEDS = WIDTH * HEIGHT;
CRGB leds[NUM_LEDS];
int position = 0; // General position for scrolling text
CRGBPalette16 currentPalette;

void setup() {
  delay(3000);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  currentPalette = RainbowColors_p;
}

// Assuming the message "JACKSON" and each letter is about 5 LEDs wide with 1 LED space
#define MESSAGE_WIDTH (7 * 5 + 6) // Total width of the message including spaces

void loop() {
  drawBackground();
  drawMessage(position, "ABCDEFGHIJKLMNOPQRSTUVWXXYZ"); // You can change the word here
  FastLED.show();

  position--;
  if (position < -MESSAGE_WIDTH) position = WIDTH;

  delay(150); // Adjust for desired speed
}

void drawMessage(int pos, const char* word) {
  int wordLength = strlen(word);
  int xOffset = 0;

  for (int i = 0; i < wordLength; i++) {
    char letter = word[i];
    switch (letter) {
      case 'A':
        drawLetterA(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'B':
        drawLetterB(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'C':
        drawLetterC(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'D':
        drawLetterD(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'E':
        drawLetterE(pos + xOffset);
        xOffset += 7; // Adjust for letter spacing
        break;
      case 'F':
        drawLetterF(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'G':
        drawLetterG(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'H':
        drawLetterH(pos + xOffset);
        xOffset += 7; // Adjust for letter spacing
        break;
      case 'I':
        drawLetterI(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'J':
        drawLetterJ(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'K':
        drawLetterK(pos + xOffset);
        xOffset += 7; // Adjust for letter spacing
        break;
      case 'L':
        drawLetterL(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'M':
        drawLetterM(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'N':
        drawLetterN(pos + xOffset);
        xOffset += 7; // Adjust for letter spacing
        break;
      case 'O':
        drawLetterO(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'P':
        drawLetterP(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'Q':
        drawLetterQ(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'R':
        drawLetterR(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'S':
        drawLetterS(pos + xOffset);
        xOffset += 7; // Adjust for letter spacing
        break;
      case 'T':
        drawLetterT(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'U':
        drawLetterU(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'V':
        drawLetterV(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'W':
        drawLetterW(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'X':
        drawLetterX(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'Y':
        drawLetterY(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      case 'Z':
        drawLetterZ(pos + xOffset);
        xOffset += 6; // Adjust for letter spacing
        break;
      default:
        // Handle spaces or other characters
        xOffset += 4; // Adjust for spacing
        break;
    }
  }
}

void drawBackground() {
  static uint8_t hue = 0;
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      uint8_t noise = inoise8(x * SCALE, y * SCALE, hue);
      leds[XY(x, y)] = ColorFromPalette(currentPalette, noise);
    }
  }
  hue++;
}

// Function to convert (x, y) to LED index in a zigzag pattern
int XY(int x, int y) {
  return y % 2 == 0 ? y * WIDTH + x : y * WIDTH + WIDTH - 1 - x;
}

void drawLetterA(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int center = WIDTH / 2 + pos;
    if (center >= 0 && center < WIDTH) {
      // Vertical lines of the "A"
      if (y != HEIGHT - 1) {
        leds[XY(center, y)] = CRGB::White;
        leds[XY(center - 1, y)] = CRGB::White;
        leds[XY(center + 1, y)] = CRGB::White;
      }
      // Top horizontal line of the "A"
      if (y == 0) {
        leds[XY(center, y)] = CRGB::White;
      }
    }
  }
}


void drawLetterB(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 3 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "B"
      leds[XY(x, y)] = CRGB::White;
    }

    if ((y == 0 || y == HEIGHT / 2 || y == HEIGHT - 1) && x < WIDTH - 1) {
      for (int i = 1; i <= 3; i++) {
        // Top, middle, and bottom horizontal lines of the "B"
        int xPos = x + i;
        if (xPos >= 0 && xPos < WIDTH) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    } else if ((y == 1 || y == HEIGHT / 2 - 1 || y == HEIGHT - 2) && x < WIDTH - 2) {
      // Curves of the "B"
      int xPos = x + 3;
      if (xPos >= 0 && xPos < WIDTH) {
        leds[XY(xPos, y)] = CRGB::White;
      }
    }
  }
}

void drawLetterC(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 3 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "C" at top and bottom
      if (y == 0 || y == HEIGHT - 1) {
        leds[XY(x, y)] = CRGB::White;
      }
      // Top and bottom horizontal lines of the "C"
      if (y == 0 || y == HEIGHT - 1) {
        for (int i = 1; i <= 3; i++) {
          int xPos = x + i;
          if (xPos >= 0 && xPos < WIDTH) {
            leds[XY(xPos, y)] = CRGB::White;
          }
        }
      }
    }
  }
}

void drawLetterD(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 3 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "D"
      leds[XY(x, y)] = CRGB::White;
    }

    if ((y == 0 || y == HEIGHT - 1) && x < WIDTH - 1) {
      for (int i = 1; i <= 3; i++) {
        // Top and bottom horizontal lines of the "D"
        int xPos = x + i;
        if (xPos >= 0 && xPos < WIDTH) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    } else if ((y == 1 || y == HEIGHT - 2) && x < WIDTH - 2) {
      // Curves of the "D"
      int xPos = x + 3;
      if (xPos >= 0 && xPos < WIDTH) {
        leds[XY(xPos, y)] = CRGB::White;
      }
    }
  }
}


void drawLetterE(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 3 + pos;
    if (x >= 0 && x < WIDTH) {
      leds[XY(x, y)] = CRGB::White; // Vertical line
    }

    if (y == 0 || y == HEIGHT / 2 || y == HEIGHT - 1) {
      for (int i = 1; i <= 3; i++) { // Top, middle, and bottom horizontal lines
        x = WIDTH / 2 - 3 + pos + i;
        if (x >= 0 && x < WIDTH) {
          leds[XY(x, y)] = CRGB::White;
        }
      }
    }
  }
}

void drawLetterF(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 3 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "F"
      leds[XY(x, y)] = CRGB::White;
    }

    if (y == 0 || y == HEIGHT / 2) {
      for (int i = 1; i <= 3; i++) {
        // Top and middle horizontal lines of the "F"
        int xPos = x + i;
        if (xPos >= 0 && xPos < WIDTH) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}

void drawLetterG(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 3 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "G" at top and bottom
      if (y == 0 || y == HEIGHT - 1) {
        leds[XY(x, y)] = CRGB::White;
      }
      // Top and bottom horizontal lines of the "G"
      if (y == 0 || y == HEIGHT - 1 || (y == HEIGHT / 2 && x >= WIDTH / 2 - 3)) {
        for (int i = 1; i <= 3; i++) {
          int xPos = x + i;
          if (xPos >= 0 && xPos < WIDTH) {
            leds[XY(xPos, y)] = CRGB::White;
          }
        }
      }
      // Right vertical line of "G" in the middle
      if (x == WIDTH / 2 && y >= HEIGHT / 2) {
        leds[XY(x, y)] = CRGB::White;
      }
    }
  }
}


void drawLetterH(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 3; x <= WIDTH / 2 + 2; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Vertical lines of the "H"
        if (x == WIDTH / 2 - 3 || x == WIDTH / 2 + 2) {
          leds[XY(xPos, y)] = CRGB::White;
        }
        // Horizontal line of the "H"
        if (y == HEIGHT / 2) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}


void drawLetterI(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 1 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "I"
      leds[XY(x, y)] = CRGB::White;
    }
    if ((y == 0 || y == HEIGHT - 1) && (x >= WIDTH / 2 - 3 && x <= WIDTH / 2 + 1)) {
      // Top and bottom horizontal lines of the "I"
      for (int i = -2; i <= 2; i++) {
        int xPos = x + i;
        if (xPos >= 0 && xPos < WIDTH) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}

void drawLetterJ(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 1 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "J"
      if (y > HEIGHT / 2 || y == HEIGHT - 1) {
        leds[XY(x, y)] = CRGB::White;
      }
      // Bottom horizontal line of the "J"
      if (y == HEIGHT - 1) {
        for (int i = 1; i <= 3; i++) {
          int xPos = x - i;
          if (xPos >= 0 && xPos < WIDTH) {
            leds[XY(xPos, y)] = CRGB::White;
          }
        }
      }
    }
  }
}

void drawLetterK(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 3 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "K"
      leds[XY(x, y)] = CRGB::White;

      // Diagonal lines of the "K"
      int mid = HEIGHT / 2;
      if (y < mid) {
        int xPos = x + (mid - y);
        if (xPos >= 0 && xPos < WIDTH) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      } else {
        int xPos = x + (y - mid);
        if (xPos >= 0 && xPos < WIDTH) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}

void drawLetterL(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 3 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "L"
      leds[XY(x, y)] = CRGB::White;

      // Bottom horizontal line of the "L"
      if (y == 0) {
        for (int i = 1; i <= 3; i++) {
          int xPos = x + i;
          if (xPos >= 0 && xPos < WIDTH) {
            leds[XY(xPos, y)] = CRGB::White;
          }
        }
      }
    }
  }
}

void drawLetterM(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 4; x <= WIDTH / 2 + 3; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Vertical lines of the "M"
        if (x == WIDTH / 2 - 4 || x == WIDTH / 2 + 3) {
          leds[XY(xPos, y)] = CRGB::White;
        }
        // Diagonal lines of the "M"
        if ((x == WIDTH / 2 - 2 && y <= 2) || (x == WIDTH / 2 + 1 && y <= 2)) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}

void drawLetterN(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 4; x <= WIDTH / 2 + 3; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Vertical lines of the "N"
        if (x == WIDTH / 2 - 4 || x == WIDTH / 2 + 3) {
          leds[XY(xPos, y)] = CRGB::White;
        }
        // Diagonal line of the "N"
        if (x - (WIDTH / 2 - 4) == y) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}

void drawLetterO(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 3; x <= WIDTH / 2 + 2; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Vertical lines of the "O"
        if (x == WIDTH / 2 - 3 || x == WIDTH / 2 + 2) {
          leds[XY(xPos, y)] = CRGB::White;
        }
        // Top and bottom horizontal lines of the "O"
        if ((y == 0 || y == HEIGHT - 1) && (x > WIDTH / 2 - 3 && x < WIDTH / 2 + 2)) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}


void drawLetterP(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 3 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "P"
      leds[XY(x, y)] = CRGB::White;
    }

    if (y == 0 || y == HEIGHT / 2) {
      for (int i = 1; i <= 3; i++) {
        // Top and middle horizontal lines of the "P"
        int xPos = x + i;
        if (xPos >= 0 && xPos < WIDTH) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    } else if ((y == 1 || y == HEIGHT / 2 - 1) && x < WIDTH - 2) {
      // Curves of the "P"
      int xPos = x + 3;
      if (xPos >= 0 && xPos < WIDTH) {
        leds[XY(xPos, y)] = CRGB::White;
      }
    }
  }
}

void drawLetterQ(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 3; x <= WIDTH / 2 + 2; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Vertical lines of the "Q"
        if (x == WIDTH / 2 - 3 || x == WIDTH / 2 + 2) {
          leds[XY(xPos, y)] = CRGB::White;
        }
        // Top and bottom horizontal lines of the "Q"
        if ((y == 0 || y == HEIGHT - 1) && (x > WIDTH / 2 - 3 && x < WIDTH / 2 + 2)) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
    // Diagonal line of "Q"
    if (pos + WIDTH / 2 - 1 >= 0 && pos + WIDTH / 2 - 1 < WIDTH && y == HEIGHT - 2) {
      leds[XY(pos + WIDTH / 2 - 1, y)] = CRGB::White;
    }
  }
}

void drawLetterR(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 3 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "R"
      leds[XY(x, y)] = CRGB::White;
    }

    if (y == 0 || y == HEIGHT / 2) {
      for (int i = 1; i <= 3; i++) {
        // Top and middle horizontal lines of the "R"
        int xPos = x + i;
        if (xPos >= 0 && xPos < WIDTH) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    } else if ((y == 1 || y == HEIGHT / 2 - 1) && x < WIDTH - 2) {
      // Curves of the "R"
      int xPos = x + 3;
      if (xPos >= 0 && xPos < WIDTH) {
        leds[XY(xPos, y)] = CRGB::White;
      }
    } else if (y > HEIGHT / 2 && y - HEIGHT / 2 == x - WIDTH / 2) {
      // Diagonal line of the "R"
      int xPos = x + y - HEIGHT / 2;
      if (xPos >= 0 && xPos < WIDTH) {
        leds[XY(xPos, y)] = CRGB::White;
      }
    }
  }
}

void drawLetterS(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 3; x <= WIDTH / 2 + 2; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Top, middle, and bottom horizontal lines of the "S"
        if ((y == 0 || y == HEIGHT / 2 || y == HEIGHT - 1) && (x > WIDTH / 2 - 3 && x < WIDTH / 2 + 2)) {
          leds[XY(xPos, y)] = CRGB::White;
        }
        // Top left and bottom right vertical lines of the "S"
        if ((y < HEIGHT / 2 && x == WIDTH / 2 - 3) || (y > HEIGHT / 2 && x == WIDTH / 2 + 2)) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}

void drawLetterT(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    int x = WIDTH / 2 - 1 + pos;
    if (x >= 0 && x < WIDTH) {
      // Vertical line of the "T"
      if (y > 0) {
        leds[XY(x, y)] = CRGB::White;
      }
    }
    // Top horizontal line of the "T"
    if (y == 0) {
      for (int i = -2; i <= 2; i++) {
        int xPos = x + i;
        if (xPos >= 0 && xPos < WIDTH) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}

void drawLetterU(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 3; x <= WIDTH / 2 + 2; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Vertical lines of the "U"
        if ((x == WIDTH / 2 - 3 || x == WIDTH / 2 + 2) && y < HEIGHT - 1) {
          leds[XY(xPos, y)] = CRGB::White;
        }
        // Bottom horizontal line of the "U"
        if (y == HEIGHT - 1 && x > WIDTH / 2 - 3 && x < WIDTH / 2 + 2) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}
void drawLetterV(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 4; x <= WIDTH / 2 + 3; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Diagonal lines of the "V"
        if (x - (WIDTH / 2 - 4) == y / 2 || x == WIDTH / 2 + 3 - y / 2) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}

void drawLetterW(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 4; x <= WIDTH / 2 + 4; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Vertical lines of the "W"
        if (x == WIDTH / 2 - 4 || x == WIDTH / 2 + 4) {
          leds[XY(xPos, y)] = CRGB::White;
        }
        // Inner diagonal lines of the "W"
        if ((x == WIDTH / 2 - 2 && y >= HEIGHT / 2) || (x == WIDTH / 2 + 2 && y >= HEIGHT / 2)) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}

void drawLetterX(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 3; x <= WIDTH / 2 + 2; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Diagonal lines of the "X"
        if (x - (WIDTH / 2 - 3) == y || x == WIDTH / 2 + 2 - y) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}
void drawLetterY(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 3; x <= WIDTH / 2 + 2; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Upper diagonal lines of the "Y"
        if ((y < HEIGHT / 2 && (x - (WIDTH / 2 - 3) == y || x == WIDTH / 2 + 2 - y))) {
          leds[XY(xPos, y)] = CRGB::White;
        }
        // Vertical line of the "Y"
        if (y >= HEIGHT / 2 && x == WIDTH / 2 - 1) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}

void drawLetterZ(int pos) {
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = WIDTH / 2 - 3; x <= WIDTH / 2 + 2; x++) {
      int xPos = x + pos;
      if (xPos >= 0 && xPos < WIDTH) {
        // Top and bottom horizontal lines of the "Z"
        if (y == 0 || y == HEIGHT - 1) {
          leds[XY(xPos, y)] = CRGB::White;
        }
        // Diagonal line of the "Z"
        if (x == WIDTH / 2 + 2 - y) {
          leds[XY(xPos, y)] = CRGB::White;
        }
      }
    }
  }
}



