#ifndef SRC_TIME_CONFIG_CONTROLLER_H_
#define SRC_TIME_CONFIG_CONTROLLER_H_

#include "core/event_consumer.h"

class TimeDisplayController;

class TimeConfigController : public EventConsumer {
 public:
  TimeConfigController();
  TimeConfigController(TimeDisplayController* time_display_controller);

  void HandleEvent(const Event& event) override;

 private:
  TimeDisplayController* time_display_controller_;
};

#endif
