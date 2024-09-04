#include "time_display_controller.h"

#include "core/display.h"
#include "core/time_of_day_clock.h"
#include "time_config_controller.h"
#include "core/color.h"

void RenderTime(Display* display, TimeOfDayClock* clock, uint32_t color) {
  SevenSegment* ss = display->sevensegment;
  ss[0].RenderBitmap(Bitmap::kDigit[clock->GetHours() % 10], color);
  ss[1].RenderBitmap(Bitmap::kDigit[clock->GetHours() / 10], color);
  ss[2].RenderBitmap(Bitmap::kDigit[clock->GetMinutes() % 10], color);
  ss[3].RenderBitmap(Bitmap::kDigit[clock->GetMinutes() / 10], color);
  ss[4].RenderBitmap(Bitmap::kDigit[clock->GetSeconds() % 10], color);
  ss[5].RenderBitmap(Bitmap::kDigit[clock->GetSeconds() / 10], color);
}

TimeDisplayController::TimeDisplayController()
    : kernel_(nullptr),
      time_config_controller_(nullptr),
      switch_animation_(this) {}

void TimeDisplayController::Init(Kernel* kernel,
                                 TimeConfigController* time_config_controller) {
  kernel_ = kernel;
  time_config_controller_ = time_config_controller;
}

void TimeDisplayController::HandleEvent(const Event& event) {
  switch (event.type) {
    case Event::kDraw: {
      Display* display = kernel_->GetDisplay();
      TimeOfDayClock* clock = kernel_->GetTimeOfDayClock();
      RenderTime(display, clock, Color::kRed);
      break;
    }
    case Event::kButtonLongPressStart: {
      kernel_->SetFocus(&switch_animation_);
      break;
    }
    default:
      break;
  }
}

TimeDisplayController::SwitchAnimation::SwitchAnimation(
    TimeDisplayController* parent)
    : parent_(parent) {}

void TimeDisplayController::SwitchAnimation::HandleEvent(const Event& event) {
  switch (event.type) {
    case Event::kButtonLongPressFinish: {
      parent_->kernel_->SetFocus(parent_->time_config_controller_);
      break;
    }
    case Event::kButtonLongPressInterrupt: {
      parent_->kernel_->SetFocus(parent_);
      break;
    }
    case Event::kDraw: {
      Display* display = parent_->kernel_->GetDisplay();
      TimeOfDayClock* clock = parent_->kernel_->GetTimeOfDayClock();
      // TODO: make it red and blinking
      RenderTime(display, clock, Color::kBlue);
      break;
    }
    default:
      break;
  }
}
