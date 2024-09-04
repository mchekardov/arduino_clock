#ifndef SRC_CORE_BUTTON_H_
#define SRC_CORE_BUTTON_H_

#include <Arduino.h>

#include "event_producer.h"

class Debouncer {
 public:
  Debouncer();
  Debouncer(uint8_t pin);

  bool GetState() const;
  bool HasStateChanged() const;

  void SetPin(uint8_t new_pin);

  void Update();

 private:
  static constexpr uint32_t kDebounceDelayMillis = 20;

  uint8_t pin_ = 0;
  uint32_t last_state_change_ms_ = 0;
  bool debounced_state_ = false, unstable_state_ = false,
       state_changed_ = false;
};

class Button : public EventProducer {
 public:
  Button();
  void Init(uint8_t pin, int16_t id);

  void SetPin(uint8_t new_pin);
  void SetId(int16_t new_id);

  void Poll(Kernel* kernel);

 private:
  static constexpr uint32_t kClickTreshold = 1000;
  static constexpr uint32_t kLongPressDuration = 3000;

  Debouncer debouncer_;
  int16_t id_;
  uint32_t last_press_begin_ms_ = 0;
  bool long_press_ongoing_ = false, long_press_finished_ = false;
};

#endif
