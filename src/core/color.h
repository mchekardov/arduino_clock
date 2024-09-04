#ifndef SRC_CORE_COLOR_H_
#define SRC_CORE_COLOR_H_

#include <Arduino.h>

namespace Color {
// clang-format off
[[maybe_unused]] constexpr uint32_t
  kBlack =       0x00000000,
  kWhite =       0x00ffffff,
  kDarkGray =    0x00808080,
  kGray =        0x00a0a0a4,
  kLightGray =   0x00c0c0c0,
  kRed =         0x00ff0000,
  kBlue =        0x0000ff00,
  kGreen =       0x000000ff,
  kCyan =        0x0000ffff,
  kMagenta =     0x00ff00ff,
  kYellow =      0x00ffff00,
  kDarkRed =     0x00800000,
  kDarkGreen =   0x00008000,
  kDarkBlue =    0x00000080,
  kDarkCyan =    0x00008080,
  kDarkMagenta = 0x00800080,
  kDarkYellow =  0x00808000;
// clang-format on

uint32_t MakeColor(uint8_t red, uint8_t blue, uint8_t green);
uint8_t GetRed(uint32_t color);
uint8_t GetGreen(uint32_t color);
uint8_t GetBlue(uint32_t color);

uint32_t InterpolateLinear(uint32_t color1, uint32_t color2, float fraction);

};  // namespace Color

#endif
