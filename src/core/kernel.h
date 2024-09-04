#ifndef SRC_CORE_KERNEL_H_
#define SRC_CORE_KERNEL_H_

#include "../util/static_queue.h"
#include "../util/static_vector.h"
#include "display.h"
#include "event_consumer.h"
#include "event_producer.h"
#include "time_of_day_clock.h"
#include "timer.h"

class Kernel {
 public:
  Kernel();

  Display* GetDisplay();
  TimeOfDayClock* GetTimeOfDayClock();
  void* GetSharedState();

  void SetFocus(EventConsumer* focus);
  void SetSharedState(void* shared_state);
  void RegisterExternalEventProducer(EventProducer* event_producer);
  void PostEvent(const Event& event);

  int16_t CreateTimer(uint32_t interval_ms, bool oneshot = true);
  void StopTimer(int16_t id);

  void Loop();

 private:
  static constexpr uint16_t kEventQueueCapacity = 16;
  static constexpr uint16_t kEventSourcesCapacity = 8;
  static constexpr uint16_t kTimerPoolCapacity = 4;
  static constexpr uint32_t kNumFramesPerSecond = 30;
  static constexpr uint32_t kFrameDelayMillis = 1000 / kNumFramesPerSecond;

  EventConsumer* focus_ = nullptr;
  uint32_t previous_frame_ms_ = 0;
  Display display_;
  TimeOfDayClock time_of_day_clock_;
  void* shared_state_ = nullptr;
  static_queue<Event, 16> event_queue_;
  static_vector<EventProducer*, 8> external_event_producers_;
  Timer timer_pool_[kTimerPoolCapacity];
};

#endif
