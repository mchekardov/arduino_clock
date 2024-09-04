#include "timer.h"

#include "event.h"
#include "kernel.h"
#include "../util/log.h"

Timer::Timer(int16_t id) : id_(id) {}

bool Timer::IsActive() const { return active_; }
int16_t Timer::GetId() const { return id_; }

Timer& Timer::SetId(int16_t new_id) {
  id_ = new_id;
  return *this;
}
Timer& Timer::SetInterval(uint32_t new_interval_ms) {
  interval_ms_ = new_interval_ms;
  return *this;
}
Timer& Timer::SetOneshot(bool new_oneshot) {
  oneshot_ = new_oneshot;
  return *this;
}
Timer& Timer::Start() {
  static const PROGMEM char kLogScope[] = "Timer::Start: ";
  if (active_) {
    Log.Warning(kLogScope, F("Attempting to start an already active timer"));
  }
  active_ = true;
  return *this;
}
Timer& Timer::Stop() {
  active_ = false;
  return *this;
}

void Timer::Poll(Kernel* kernel) {
  if (!active_) return;
  uint32_t time_delta = millis() - started_ms_;
  if (time_delta <= interval_ms_) {
    started_ms_ += interval_ms_;
    active_ = !oneshot_;
    kernel->PostEvent(TimerEvent(id_));
  }
}
