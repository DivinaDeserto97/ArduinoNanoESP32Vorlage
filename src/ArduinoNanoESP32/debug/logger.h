#pragma once
#include <Arduino.h>

namespace Log {

// Optional: Level (falls du später filtern willst)
enum class Level : uint8_t { DEBUG, INFO, SUCCESS, WARNING, ERROR };

void begin(bool enableColors = true);

// einfache Messages
void debug(const char* msg);
void info(const char* msg);
void success(const char* msg);
void warning(const char* msg);
void error(const char* msg);

// printf-style (mit Variablen)
void debugf(const char* fmt, ...);
void infof(const char* fmt, ...);
void successf(const char* fmt, ...);
void warningf(const char* fmt, ...);
void errorf(const char* fmt, ...);

} // namespace Log
