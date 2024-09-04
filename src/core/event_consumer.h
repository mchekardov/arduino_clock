#ifndef SRC_CORE_EVENT_CONSUMER_H_
#define SRC_CORE_EVENT_CONSUMER_H_

#include "event.h"

class EventConsumer {
 public:
  virtual void HandleEvent(const Event& event) = 0;
};

#endif
