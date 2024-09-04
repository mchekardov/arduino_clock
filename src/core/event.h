#ifndef SRC_CORE_EVENT_H_
#define SRC_CORE_EVENT_H_

#include <Arduino.h>

struct Event {
  enum Type {
    kNone,
    kDraw,
    kButtonPress,
    kButtonRelease,
    kButtonClick,
    kButtonLongPressStart,
    kButtonLongPressInterrupt,
    kButtonLongPressFinish,
    kFocusIn,
    kFocusOut,
    kTimerEvent,
  } type;
  union {
    int16_t id;
  } data;
};

inline Event DrawEvent() { return {.type = Event::kDraw, .data = {}}; }
inline Event ButtonEvent(Event::Type type, int16_t id) {
  return {.type = type, .data = {.id = id}};
}
inline Event ButtonPressEvent(int16_t id) {
  return ButtonEvent(Event::kButtonPress, id);
}
inline Event ButtonReleaseEvent(int16_t id) {
  return ButtonEvent(Event::kButtonRelease, id);
}
inline Event ButtonClickEvent(int16_t id) {
  return ButtonEvent(Event::kButtonClick, id);
}
inline Event ButtonLongPressStartEvent(int16_t id) {
  return ButtonEvent(Event::kButtonLongPressStart, id);
}
inline Event ButtonLongPressInterruptEvent(int16_t id) {
  return ButtonEvent(Event::kButtonLongPressInterrupt, id);
}
inline Event ButtonLongPressFinishEvent(int16_t id) {
  return ButtonEvent(Event::kButtonLongPressFinish, id);
}
inline Event FocusInEvent() { return {.type = Event::kFocusIn, .data = {}}; }
inline Event FocusOutEvent() { return {.type = Event::kFocusOut, .data = {}}; }
inline Event TimerEvent(int16_t id) {
  return {.type = Event::kTimerEvent, .data = {.id = id}};
}

#endif
