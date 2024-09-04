#ifndef SRC_CORE_TIME_OF_DAY_CLOCK_H_
#define SRC_CORE_TIME_OF_DAY_CLOCK_H_

#include <Arduino.h>

class TimeOfDayClock {
 public:
  TimeOfDayClock();

  void AddMillis(int32_t millis);
  void AddSeconds(int32_t seconds);
  void AddMinutes(int32_t minutes);
  void AddHours(int32_t hours);

  int32_t GetMillis() const;
  int32_t GetSeconds() const;
  int32_t GetMinutes() const;
  int32_t GetHours() const;

  void Sync();

 private:
  static constexpr int32_t kMillisInSecond = 1000;
  static constexpr int32_t kMillisInMinute = 1000 * 60;
  static constexpr int32_t kMillisInHour = 1000 * 60 * 60;
  static constexpr int32_t kMillisInDay = 1000 * 60 * 60 * 24;
  static constexpr int32_t kSecondsInDay = 60 * 60 * 24;
  static constexpr int32_t kMinutesInDay = 60 * 24;
  static constexpr int32_t kHoursInDay = 24;

  int32_t time_of_day_ms_ = 0;
  uint32_t last_sync_ms_ = 0;
};

#endif
