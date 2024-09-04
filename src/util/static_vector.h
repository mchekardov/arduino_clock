#ifndef SRC_UTIL_STATIC_VECTOR_H_
#define SRC_UTIL_STATIC_VECTOR_H_

#include <Arduino.h>

#include "log.h"

template <typename T, uint16_t Capacity>
class static_vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;

  static_vector() = default;
  void assign(size_t n, const value_type& u) {
    for (size_t i = 0; i < n; ++i) {
      data_[i] = u;
    }
  }

  uint16_t size() const noexcept { return end_; }
  bool empty() const noexcept { return end_ == 0; }

  reference operator[](uint16_t n) {
    if (n >= Capacity) {
      Log.Error(F("static_vector: operator[]: index out of bounds (Capacity="),
                Capacity, F(", index="), n, ")");
    }
    return data_[n];
  }
  const_reference operator[](uint16_t n) const {
    if (n >= Capacity) {
      Log.Error(F("static_vector: operator[]: index out of bounds (Capacity="),
                Capacity, F(", index="), n, ")");
    }
    return data_[n];
  }

  reference front() { return data_[0]; }
  const_reference front() const { return data_[0]; }
  reference back() { return data_[end_ - 1]; }
  const_reference back() const { return data_[end_ - 1]; }

  T* data() { return &data_; }
  const T* data() const { return &data_; }

  void push_back(const value_type& x) {
    if (end_ >= Capacity) {
      Log.Error(F("static_vector: push_back: capacity overflow (Capacity="),
                Capacity, ")");
    }
    data_[end_++] = x;
  }
  template <typename... Args>
  reference emplace_back(Args&&... args) {
    if (end_ >= Capacity) {
      Log.Error(F("static_vector: emplace_back: capacity overflow (Capacity="),
                Capacity, ")");
    }
    return data_[end_++] = T{forward(args...)};
  }
  void pop_back() {
    if (end_ == 0) {
      Log.Error(F("static_vector: pop_back: vector is empty"));
    }
    --end_;
  }

  void clear() noexcept { end_ = 0; }

 private:
  uint16_t end_{0};
  T data_[Capacity];
};

#endif
