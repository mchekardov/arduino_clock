#include "kernel.h"

#include "../util/log.h"

Kernel::Kernel() {
  for (uint16_t i = 0; i < kTimerPoolCapacity; i++) {
    timer_pool_[i] = Timer(i);
  }
}

Display* Kernel::GetDisplay() { return &display_; }
TimeOfDayClock* Kernel::GetTimeOfDayClock() { return &time_of_day_clock_; }
void* Kernel::GetSharedState() { return shared_state_; }

void Kernel::SetFocus(EventConsumer* focus) {
  static const PROGMEM char kLogScope[] = "Kernel::SetFocus: ";
  Log.Info(kLogScope, F("Received focus update with focus="),
           (unsigned long)focus);
  if (focus_) {
    focus_->HandleEvent(FocusOutEvent());
  }
  focus_ = focus;
  if (focus_) {
    focus_->HandleEvent(FocusInEvent());
  }
}
void Kernel::SetSharedState(void* shared_state) {
  shared_state_ = shared_state;
}
void Kernel::RegisterExternalEventProducer(EventProducer* event_producer) {
  static const PROGMEM char kLogScope[] = "Kernel::RegisterEventProducer: ";
  Log.Info(kLogScope, F("Registered new event producer at "),
           (unsigned long)event_producer);
  external_event_producers_.push_back(event_producer);
}
void Kernel::PostEvent(const Event& event) { event_queue_.push(event); }

int16_t Kernel::CreateTimer(uint32_t interval_ms, bool oneshot) {
  static const PROGMEM char kLogScope[] = "Kernel::CreateTimer: ";
  for (uint16_t i = 0; i < kTimerPoolCapacity; i++) {
    if (!timer_pool_[i].IsActive()) {
      int16_t id = timer_pool_[i].GetId();
      timer_pool_[i].SetInterval(interval_ms).SetOneshot(oneshot).Start();
      Log.Info(kLogScope, F("Created a timer with id="), id, F(", interval="),
               interval_ms, F("ms, oneshot="), (int)oneshot);
      return id;
    }
  }
  Log.Info(kLogScope, F("Failed to create a timer"));
  return -1;
}
void Kernel::StopTimer(int16_t id) {
  for (uint16_t i = 0; i < kTimerPoolCapacity; i++) {
    if (id == timer_pool_[i].GetId()) {
      timer_pool_[i].Stop();
    }
  }
}

void Kernel::Loop() {
  const static PROGMEM char kLogScope[] = "Kernel::Loop: ";
  if (!focus_) {
    Log.Warning(kLogScope, F("Focus is nullptr"));
    return;
  }
  // Collect events
  for (uint16_t i = 0; i < external_event_producers_.size(); ++i) {
    external_event_producers_[i]->Poll(this);
  }
  for (uint16_t i = 0; i < kTimerPoolCapacity; ++i) {
    timer_pool_[i].Poll(this);
  }
  // Dispatch events
  while (focus_ && !event_queue_.empty()) {
    focus_->HandleEvent(event_queue_.front());
    event_queue_.pop();
  }
  // Send a draw event if necessary
  uint32_t current_frame_ms = millis(),
           frame_delta_ms = current_frame_ms - previous_frame_ms_;
  if (frame_delta_ms >= kFrameDelayMillis) {
    Log.Info(kLogScope, F("Sending a draw event"));
    focus_->HandleEvent(DrawEvent());
    previous_frame_ms_ = current_frame_ms;
  }
}
