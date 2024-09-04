#ifndef SRC_UTIL_LOG_H_
#define SRC_UTIL_LOG_H_
#include <Arduino.h>

enum class LogLevel {
  kSilent = 0,
  kFatal = 1,
  kError = 2,
  kWarning = 3,
  kInfo = 4,
  kDebug = 5,
  kTrace = 6,
};

class Logger {
 public:
  Logger();

  void Begin(LogLevel level, uint32_t serial_baud_rate = 230400);

  template <typename... Args>
  void Fatal(Args... args) {
    PrintCommon(LogLevel::kFatal, F("FATAL: "), static_cast<Args&&>(args)...);
  }
  template <typename... Args>
  void Error(Args... args) {
    PrintCommon(LogLevel::kError, F("ERROR: "), static_cast<Args&&>(args)...);
  }
  template <typename... Args>
  void Warning(Args... args) {
    PrintCommon(LogLevel::kWarning, F("WARNING: "),
                static_cast<Args&&>(args)...);
  }
  template <typename... Args>
  void Info(Args... args) {
    PrintCommon(LogLevel::kInfo, F("INFO: "), static_cast<Args&&>(args)...);
  }
  template <typename... Args>
  void Debug(Args... args) {
    PrintCommon(LogLevel::kDebug, F("DEBUG: "), static_cast<Args&&>(args)...);
  }
  template <typename... Args>
  void Trace(Args... args) {
    PrintCommon(LogLevel::kTrace, F("TRACE: "), static_cast<Args&&>(args)...);
  }

 private:
  template <typename... Args>
  void PrintCommon(LogLevel message_level, Args... args) {
    if (level_ < message_level) return;
    Print(millis(), "ms: ", static_cast<Args&&>(args)...);
  }
  template <typename T>
  void Print(const T& x) {
    Serial.println(x);
  }
  template <typename T, typename... Args>
  void Print(const T& x, Args... args) {
    Serial.print(x);
    Print(static_cast<Args&&>(args)...);
  }

  LogLevel level_;
};

extern Logger Log;

#endif
