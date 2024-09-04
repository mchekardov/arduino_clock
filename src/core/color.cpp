#include "color.h"

uint8_t Color::GetRed(uint32_t c) { return (c & 0x00ff0000) >> 16; }
uint8_t Color::GetGreen(uint32_t c) { return (c & 0x000000ff); }
uint8_t Color::GetBlue(uint32_t c) { return (c & 0x0000ff00) >> 8; }
uint32_t Color::MakeColor(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) & ((uint32_t)g) & ((uint32_t)b << 8);
}

uint32_t Color::InterpolateLinear(uint32_t c1, uint32_t c2, float frac) {
  uint8_t r1 = GetRed(c1), g1 = GetGreen(c1), b1 = GetBlue(c1), r2 = GetRed(c2),
          g2 = GetGreen(c2), b2 = GetBlue(c2);
  return MakeColor((uint8_t)(r1 * frac + r2 * (1 - frac)),
                   (uint8_t)(g1 * frac + g2 * (1 - frac)),
                   (uint8_t)(b1 * frac + b2 * (1 - frac)));
}
