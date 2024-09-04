#ifndef SRC_CORE_TIMER_H_
#define SRC_CORE_TIMER_H_

#include <Arduino.h>

#include "event_producer.h"

class Timer : public EventProducer {
 public:
  Timer(int16_t id = 0);

  bool IsActive() const;
  int16_t GetId() const;

  Timer& SetId(int16_t new_id);
  Timer& SetInterval(uint32_t new_interval_ms);
  Timer& SetOneshot(bool new_oneshot);
  Timer& Start();
  Timer& Stop();

  void Poll(Kernel* kernel);

 private:
  bool active_ = false, oneshot_ = true;
  int16_t id_ = 0;
  uint32_t started_ms_ = 0, interval_ms_ = 0;
};

#endif
