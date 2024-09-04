#include "log.h"

Logger::Logger() : level_(LogLevel::kSilent) {}

void Logger::Begin(LogLevel level, uint32_t serial_baud_rate) {
  Serial.begin(serial_baud_rate);
  while(!Serial) continue;
  level_ = level;
}

Logger Log;
