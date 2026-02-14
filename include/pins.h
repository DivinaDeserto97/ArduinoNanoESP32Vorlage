#pragma once
#include <Arduino.h> // Arduino Grundfunktionen

// Baudrate für Serial Monitor
static const uint32_t SERIAL_BAUD = 115200;

static const int PIN_LED = LED_BUILTIN;   // eingebaute Board-LED
static const int PIN_RELAY = D3;          // Test-Ausgang an D2 (später PC-Powertaster/Relais/Transistor)

