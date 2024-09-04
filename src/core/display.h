#ifndef SRC_CORE_DISPLAY_H_
#define SRC_CORE_DISPLAY_H_

#include "Adafruit_NeoPixel.h"

/*
 * LED order:
 * ┌───────┐
 * │/←←3←←\│
 * │↓┌───┐↑│
 * │↓│   │↑│
 * │4│   │2│
 * │↓│   │↑│
 * │↓└───┘↑│
 * │↓  1→→/│
 * │↓┌───┐ │
 * │↓│   │ │
 * │5│   │7│
 * │↓│   │↑│
 * │↓└───┘↑│
 * │\→→6→→/│
 * └───────┘
 */

namespace Bitmap {
// TODO: make bitmaps for letters
// clang-format off
[[maybe_unused]] constexpr uint8_t
  k0 = 0b01111110,
  k1 = 0b01000010,
  k2 = 0b00110111,
  k3 = 0b01100111,
  k4 = 0b01001011,
  k5 = 0b01101101,
  k6 = 0b01111101,
  k7 = 0b01000110,
  k8 = 0b01111111,
  k9 = 0b01101111;
// clang-format on

[[maybe_unused]] constexpr uint8_t kDigit[10] = {k0, k1, k2, k3, k4,
                                                 k5, k6, k7, k8, k9};
}  // namespace Bitmap

class SevenSegment {
 public:
  SevenSegment();
  void Init(uint8_t pin);

  Adafruit_NeoPixel& GetStrip();

  void SetPin(uint8_t new_pin);
  void SetSegmentColor(int16_t segment, uint32_t color);
  void RenderBitmap(uint8_t bitmap, uint32_t color, bool flush = true);
  void Clear(bool flush = true);
  void Flush();

 private:
  static constexpr int16_t kNumSegmentPixels = 2;

  Adafruit_NeoPixel strip_;
};

class Separator {
 public:
  Separator();
  void Init(uint8_t pin);

  Adafruit_NeoPixel& GetStrip();

  void SetPin(uint8_t new_pin);
  void SetColor(uint32_t color, bool flush = true);
  void Clear(bool flush = true);
  void Flush();

 private:
  static constexpr int16_t kNumPixels = 2;

  Adafruit_NeoPixel strip_;
};

struct Display {
  static constexpr int16_t kNumSevensegments = 6;
  static constexpr int16_t kNumSeparators = 2;

  Display();
  void Init(uint8_t sevensegment_pins[kNumSevensegments],
            uint8_t separator_pins[kNumSeparators]);

  void Clear();

  SevenSegment sevensegment[kNumSevensegments];
  Separator separator[kNumSeparators];
};

#endif
