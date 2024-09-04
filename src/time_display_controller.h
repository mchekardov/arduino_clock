#ifndef SRC_TIME_DISPLAY_CONTROLLER_H_
#define SRC_TIME_DISPLAY_CONTROLLER_H_

#include "core/event_consumer.h"
#include "core/kernel.h"

class TimeConfigController;
class TimeDisplayController;

class TimeDisplayController : public EventConsumer {
 public:
  TimeDisplayController();

  void Init(Kernel* kernel, TimeConfigController* time_config_controller);
  void HandleEvent(const Event& event) override;

 private:
  class SwitchAnimation : public EventConsumer {
   public:
    SwitchAnimation(TimeDisplayController* parent);

    void HandleEvent(const Event& event) override;

   private:
    static constexpr uint32_t kBlinkIntervalMillis = 1000;

    TimeDisplayController* parent_;
    uint32_t blink_start_;
  };

  void Draw();

  Kernel* kernel_;
  TimeConfigController* time_config_controller_;
  SwitchAnimation switch_animation_;
};

#endif
