#ifndef SRC_UTIL_STATIC_QUEUE_H_
#define SRC_UTIL_STATIC_QUEUE_H_

#include <Arduino.h>
#include "log.h"

template <typename T, size_t Capacity>
class static_queue {
public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  static_queue() = default;

  uint16_t size() const noexcept { return size_; }
  bool empty() const noexcept { return size_ == 0; }

  reference front() { return data_[begin_]; }
  const_reference front() const { return data_[begin_]; }
  reference back() { return data_[(end_ + Capacity - 1) % Capacity]; }
  const_reference back() const { return data_[(end_ + Capacity - 1) % Capacity]; }

  void push(const value_type& obj) {
    if (size_ == Capacity) {
      Log.Error(F("static_queue: push: capacity overflow (Capacity="), Capacity, ")");
    }
    size_++;
    data_[end_] = obj;
    end_ = (end_ + 1) % Capacity;
  }
  template <typename... Args>
  reference emplace(Args&&... args) {
    if (size_ == Capacity) {
      Log.Error(F("static_queue: emplace: capacity overflow (Capacity="), Capacity, ")");
    }
    size_++;
    data_[end_] = T{forward(args...)};
    end_ = (end_ + 1) % Capacity;
  }
  void pop() {
    if (size_ <= 0) {
      Log.Error(F("static_queue: pop: queue is empty"));
    }
    size_--;
    begin_ = (begin_ + 1) % Capacity;
  }
  void clear() {
    begin_ = 0, end_ = 0, size_ = 0;
  }

 private:
  uint16_t begin_{0};
  uint16_t end_{0};
  uint16_t size_{0};
  T data_[Capacity];
};

#endif
