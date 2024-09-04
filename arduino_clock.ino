#include "src/core/button.h"
#include "src/core/display.h"
#include "src/core/kernel.h"
#include "src/time_display_controller.h"
#include "src/util/log.h"

constexpr uint8_t kButtonPins[] = {9, 10, 11, 12};
constexpr uint8_t kSevenSegmentPins[] = {3, 4, 5, 6, 7, 8};
constexpr uint8_t kSeparatorPins[] = {2, 2};

Button buttons[4];
Kernel kernel;
TimeDisplayController time_display_controller;

void setup() {
  Log.Begin(LogLevel::kInfo);
  for (int i = 0; i < 4; ++i) {
    buttons[i].Init(kButtonPins[i], i);
    kernel.RegisterExternalEventProducer(&buttons[i]);
  }
  kernel.GetDisplay()->Init(kSevenSegmentPins, kSeparatorPins);
  time_display_controller.Init(&kernel, nullptr /* Not implemented yet */);
  kernel.SetFocus(&time_display_controller);
}

void loop() { kernel.Loop(); }
