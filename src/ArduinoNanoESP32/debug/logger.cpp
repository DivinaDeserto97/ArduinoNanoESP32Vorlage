#include "logger.h"
#include <stdarg.h>

namespace Log {

static bool g_colors = true;

// ANSI Farben
static const char* COL_RESET  = "\033[0m";
static const char* COL_RED    = "\033[31m";
static const char* COL_GREEN  = "\033[32m";
static const char* COL_YELLOW = "\033[33m";
static const char* COL_BLUE   = "\033[34m";
static const char* COL_CYAN   = "\033[36m";

static void prefix(const char* color, const char* tag) {
  if (g_colors && color) Serial.print(color);
  Serial.print(tag);
  if (g_colors) Serial.print(COL_RESET);
  Serial.print(' ');
}

static void vprintLine(const char* color, const char* tag, const char* fmt, va_list args) {
  prefix(color, tag);

  char buf[192];
  vsnprintf(buf, sizeof(buf), fmt, args);
  Serial.println(buf);
}

void begin(bool enableColors) {
  g_colors = enableColors;
}

/* --- Plain --- */
void debug(const char* msg)   { prefix(COL_CYAN,  "[DEBUG]"); Serial.println(msg); }
void info(const char* msg)    { prefix(COL_BLUE,  "[INFO ]"); Serial.println(msg); }
void success(const char* msg) { prefix(COL_GREEN, "[OK   ]"); Serial.println(msg); }
void warning(const char* msg) { prefix(COL_YELLOW,"[WARN ]"); Serial.println(msg); }
void error(const char* msg)   { prefix(COL_RED,   "[ERROR]"); Serial.println(msg); }

/* --- Formatted --- */
void debugf(const char* fmt, ...)   { va_list a; va_start(a, fmt); vprintLine(COL_CYAN,  "[DEBUG]", fmt, a); va_end(a); }
void infof(const char* fmt, ...)    { va_list a; va_start(a, fmt); vprintLine(COL_BLUE,  "[INFO ]", fmt, a); va_end(a); }
void successf(const char* fmt, ...) { va_list a; va_start(a, fmt); vprintLine(COL_GREEN, "[OK   ]", fmt, a); va_end(a); }
void warningf(const char* fmt, ...) { va_list a; va_start(a, fmt); vprintLine(COL_YELLOW,"[WARN ]", fmt, a); va_end(a); }
void errorf(const char* fmt, ...)   { va_list a; va_start(a, fmt); vprintLine(COL_RED,   "[ERROR]", fmt, a); va_end(a); }

} // namespace Log
