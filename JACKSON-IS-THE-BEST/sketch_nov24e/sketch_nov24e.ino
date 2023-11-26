#include <FastLED.h>

// LED Matrix settings
#define WIDTH 12
#define HEIGHT 12
#define NUM_LEDS (WIDTH * HEIGHT)
#define LED_PIN 2

CRGB leds[NUM_LEDS];

// Scrolling text settings
const char *message = "Hello World! ";
int charWidth = 5; // Width of characters in pixels
int spaceBetweenChars = 1; // Space between characters in pixels
int scrollSpeed = 150; // Speed of scrolling in milliseconds

// Function to set a pixel's color
void setPixel(int x, int y, CRGB color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        leds[y * WIDTH + x] = color;
    }
}

// Function to draw a character
void drawChar(char c, int x_offset, CRGB color) {
    // Define your character set here, for example:
    uint8_t font[95][5] = {
        // 5x7 font
        // Define each character's pixel pattern here
    };

    for (int y = 0; y < 7; y++) {
        for (int x = 0; x < charWidth; x++) {
            if (font[c - 32][x] & (1 << y)) {
                setPixel(x + x_offset, y, color);
            }
        }
    }
}

void setup() {
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.show();
}

void loop() {
    static int x = WIDTH;
    int len = strlen(message) * (charWidth + spaceBetweenChars);
    for (int i = 0; i < strlen(message); i++) {
        drawChar(message[i], x + i * (charWidth + spaceBetweenChars), CRGB::White);
    }

    FastLED.show();
    FastLED.clear();
    delay(scrollSpeed);

    x--;
    if (x < -len) {
        x = WIDTH;
    }
}

// Add additional functions as needed
