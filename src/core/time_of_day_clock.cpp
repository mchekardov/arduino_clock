#include "time_of_day_clock.h"

TimeOfDayClock::TimeOfDayClock() {}

void TimeOfDayClock::AddMillis(int32_t millis) {
  millis = (millis % kMillisInDay + kMillisInDay) % kMillisInDay;
  time_of_day_ms_ = (time_of_day_ms_ + millis) % kMillisInDay;
}
void TimeOfDayClock::AddSeconds(int32_t seconds) {
  seconds = (seconds % kSecondsInDay + kSecondsInDay) % kSecondsInDay;
  time_of_day_ms_ =
      (time_of_day_ms_ + seconds * kMillisInSecond) % kMillisInDay;
}
void TimeOfDayClock::AddMinutes(int32_t minutes) {
  minutes = (minutes % kMinutesInDay + kMinutesInDay) % kMinutesInDay;
  time_of_day_ms_ =
      (time_of_day_ms_ + minutes * kMillisInMinute) % kMillisInDay;
}
void TimeOfDayClock::AddHours(int32_t hours) {
  hours = (hours % kHoursInDay + kHoursInDay) % kHoursInDay;
  time_of_day_ms_ = (time_of_day_ms_ + hours * kMillisInHour) % kMillisInDay;
}

int32_t TimeOfDayClock::GetMillis() const {
  return time_of_day_ms_ % kMillisInSecond;
}
int32_t TimeOfDayClock::GetSeconds() const {
  return (time_of_day_ms_ % kMillisInMinute) / kMillisInSecond;
}
int32_t TimeOfDayClock::GetMinutes() const {
  return (time_of_day_ms_ % kMillisInHour) / kMillisInMinute;
}
int32_t TimeOfDayClock::GetHours() const {
  return time_of_day_ms_ / kMillisInHour;
}

void TimeOfDayClock::Sync() {
  uint32_t delta = (millis() - last_sync_ms_) % kMillisInDay;
  time_of_day_ms_ = (time_of_day_ms_ + delta) % kMillisInDay;
}
