#include <Adafruit_NeoPixel.h>

// ---------------- CONFIG ----------------
#define LED_PIN     8     // Data pin
#define LED_COUNT   12    // Number of LEDs in the ring
#define BRIGHTNESS  80    // 0–255 (keep modest for USB power)
// ----------------------------------------

Adafruit_NeoPixel strip(
  LED_COUNT,
  LED_PIN,
  NEO_GRB + NEO_KHZ800
);

// ---------- SETUP ----------
void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Initialize all LEDs to OFF
}

// ---------- MAIN LOOP ----------
void loop() {
  solidColor(strip.Color(255, 0, 0), 1000);   // Red
  solidColor(strip.Color(0, 255, 0), 1000);   // Green
  solidColor(strip.Color(0, 0, 255), 1000);   // Blue
  solidColor(strip.Color(255, 255, 255), 1000); // White

  colorChase(strip.Color(255, 150, 0), 50);  // Orange chase
  rainbowCycle(5);                           // Rainbow spin
  pulse(strip.Color(128, 0, 255), 10);       // Purple pulse
}

// ---------- EFFECTS ----------

// Solid color
void solidColor(uint32_t color, int wait) {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
  delay(wait);
}

// Chase effect
void colorChase(uint32_t color, int wait) {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.clear();
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

// Rainbow wheel helper
uint32_t wheel(byte pos) {
  pos = 255 - pos;
  if (pos < 85) {
    return strip.Color(255 - pos * 3, 0, pos * 3);
  }
  if (pos < 170) {
    pos -= 85;
    return strip.Color(0, pos * 3, 255 - pos * 3);
  }
  pos -= 170;
  return strip.Color(pos * 3, 255 - pos * 3, 0);
}

// Rainbow cycle
void rainbowCycle(int wait) {
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(
        i,
        wheel((i * 256 / LED_COUNT + j) & 255)
      );
    }
    strip.show();
    delay(wait);
  }
}

// Pulse (fade in/out)
void pulse(uint32_t color, int speed) {
  for (int b = 0; b <= 255; b += 5) {
    strip.setBrightness(b);
    for (int i = 0; i < LED_COUNT; i++) {
      strip.setPixelColor(i, color);
    }
    strip.show();
    delay(speed);
  }

  for (int b = 255; b >= 0; b -= 5) {
    strip.setBrightness(b);
    strip.show();
    delay(speed);
  }

  strip.setBrightness(BRIGHTNESS); // restore
}
