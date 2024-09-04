#include "button.h"

#include <Arduino.h>

#include "kernel.h"
#include "../util/log.h"

Debouncer::Debouncer() {}
Debouncer::Debouncer(uint8_t pin) : pin_(pin) { pinMode(pin_, INPUT); }

bool Debouncer::GetState() const { return debounced_state_; }
bool Debouncer::HasStateChanged() const { return state_changed_; }
void Debouncer::SetPin(uint8_t new_pin) {
  pin_ = new_pin;
  pinMode(pin_, INPUT);
}

void Debouncer::Update() {
  static const PROGMEM char kLogScope[] = "Debouncer::Update: ";
  state_changed_ = false;
  bool reading = digitalRead(pin_);
  if (reading != unstable_state_) {
    unstable_state_ = reading;
    last_state_change_ms_ = millis();
    Log.Debug(kLogScope, F("Unstable state changed to "), (int)unstable_state_,
              F(" (pin="), pin_, F(")"));
  }
  if (millis() - last_state_change_ms_ > kDebounceDelayMillis) {
    if (unstable_state_ != debounced_state_) {
      debounced_state_ = unstable_state_;
      state_changed_ = true;
      Log.Debug(kLogScope, F("debounced state changed to "),
                (int)debounced_state_, F(" (pin="), pin_, F(")"));
    }
  }
  Log.Trace(kLogScope, F("finished"));
}

Button::Button() {}
void Button::Init(uint8_t pin, int16_t id) {
  debouncer_.SetPin(pin);
  id_ = id;
}

void Button::SetPin(uint8_t new_pin) { debouncer_.SetPin(new_pin); }
void Button::SetId(int16_t new_id) { id_ = new_id; }

void Button::Poll(Kernel* kernel) {
  static const PROGMEM char kLogScope[] = "Button::Poll: ";
  debouncer_.Update();
  if (debouncer_.HasStateChanged()) {
    Log.Debug(kLogScope, F("Button state changed to "),
              (int)debouncer_.GetState(), F(" (id="), id_, F(")"));
    if (debouncer_.GetState()) {
      last_press_begin_ms_ = millis();
      kernel->PostEvent(ButtonPressEvent(id_));
      Log.Info(kLogScope, F("Emitted ButtonPressEvent"), F(" (id="), id_,
               F(")"));
    } else {
      kernel->PostEvent(ButtonReleaseEvent(id_));
      Log.Info(kLogScope, F("Emitted ButtonReleaseEvent"), F(" (id="), id_,
               F(")"));
      if (long_press_finished_) {
        long_press_finished_ = false;
      } else if (long_press_ongoing_) {
        long_press_ongoing_ = false;
        kernel->PostEvent(ButtonLongPressInterruptEvent(id_));
        Log.Info(kLogScope, F("Emitted ButtonLongPressInterruptEvent"),
                 F(" (id="), id_, F(")"));
      } else {
        kernel->PostEvent(ButtonClickEvent(id_));
        Log.Info(kLogScope, F("Emitted ButtonClickEvent"), F(" (id="), id_,
                 F(")"));
      }
    }
  } else {
    if (debouncer_.GetState()) {
      if (long_press_finished_) {
        // noop
      } else if (long_press_ongoing_) {
        if (millis() - last_press_begin_ms_ > kLongPressDuration) {
          long_press_ongoing_ = false;
          long_press_finished_ = true;
          kernel->PostEvent(ButtonLongPressFinishEvent(id_));
          Log.Info(kLogScope, F("emitted ButtonLongPressFinishEvent"),
                   F(" (id="), id_, F(")"));
        }
      } else {
        if (millis() - last_press_begin_ms_ > kClickTreshold) {
          long_press_ongoing_ = true;
          kernel->PostEvent(ButtonLongPressStartEvent(id_));
          Log.Info(kLogScope, F("emitted ButtonLongStartEvent"), F(" (id="),
                   id_, F(")"));
        }
      }
    }
  }
}
