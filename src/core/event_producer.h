#ifndef SRC_CORE_EVENT_PRODUCER_H_
#define SRC_CORE_EVENT_PRODUCER_H_

class Kernel;

class EventProducer {
 public:
  virtual void Poll(Kernel* kernel) = 0;
};

#endif
