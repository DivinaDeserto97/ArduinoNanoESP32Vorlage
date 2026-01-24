#pragma once

// =====================================================
// PINOUT (hier definierst du alle Pins zentral)
// Vorteil: Wenn du später etwas umsteckst, änderst du nur hier.
// =====================================================

// Eingebaute LED:
// Beim Nano ESP32 ist die LED oft über LED_BUILTIN verfügbar.
// Falls das bei dir nicht stimmt, kann man später fix einen GPIO setzen.
#ifndef LED_BUILTIN
  #define LED_BUILTIN 13
#endif

static const int PIN_LED = LED_BUILTIN;
