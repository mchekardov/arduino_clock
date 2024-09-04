#include "display.h"

SevenSegment::SevenSegment() : strip_(kNumSegmentPixels * 7) {}
void SevenSegment::Init(uint8_t pin) { SetPin(pin); }

Adafruit_NeoPixel& SevenSegment::GetStrip() { return strip_; }
void SevenSegment::SetPin(uint8_t new_pin) {
  strip_.setPin(new_pin);
  strip_.begin();
}

void SevenSegment::RenderBitmap(uint8_t bitmap, uint32_t color, bool flush) {
  for (int i = 0; i < 7; ++i) {
    if (bitmap & 1) {
      SetSegmentColor(i, color);
    }
    bitmap >>= 1;
  }
  if (flush) Flush();
}
void SevenSegment::Clear(bool flush) {
  strip_.clear();
  if (flush) Flush();
}
void SevenSegment::SetSegmentColor(int16_t segment, uint32_t color) {
  for (int16_t i = 0; i < kNumSegmentPixels; ++i) {
    strip_.setPixelColor(kNumSegmentPixels * segment + i, color);
  }
}
void SevenSegment::Flush() {
  strip_.show();
  strip_.clear();
}

Separator::Separator() : strip_(kNumPixels) {}
void Separator::Init(uint8_t pin) { SetPin(pin); }

Adafruit_NeoPixel& Separator::GetStrip() { return strip_; }
void Separator::SetPin(uint8_t new_pin) {
  strip_.setPin(new_pin);
  strip_.begin();
}

void Separator::SetColor(uint32_t color, bool flush) {
  for (int i = 0; i < kNumPixels; ++i) {
    strip_.setPixelColor(i, color);
  }
  if (flush) Flush();
}
void Separator::Clear(bool flush) {
  strip_.clear();
  if (flush) Flush();
}
void Separator::Flush() {
  strip_.show();
  strip_.clear();
}

Display::Display() {
  for (int16_t i = 0; i < kNumSevensegments; ++i) {
    sevensegment[i] = SevenSegment();
  }
  for (int16_t i = 0; i < kNumSeparators; ++i) {
    separator[i] = Separator();
  }
}
void Display::Init(uint8_t sevensegment_pins[kNumSevensegments],
                   uint8_t separator_pins[kNumSeparators]) {
  for (int16_t i = 0; i < kNumSevensegments; ++i) {
    sevensegment[i].Init(sevensegment_pins[i]);
  }
  for (int16_t i = 0; i < kNumSeparators; ++i) {
    separator[i].Init(separator_pins[i]);
  }
}

void Display::Clear() {
  for (int16_t i = 0; i < kNumSevensegments; ++i) {
    sevensegment[i].Clear();
  }
  for (int16_t i = 0; i < kNumSeparators; ++i) {
    separator[i].Clear();
  }
}
