#include <Arduino.h>
#include "ArduinoNanoESP32/debug/logger.h"

const int LED_PIN = LED_BUILTIN;

unsigned long lastUptime = 0;
bool led = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  while (!Serial) { delay(10); }

  Log::begin(true); // Farben an (false = keine Farbcodes)

  Log::info("System gestartet");
  Log::successf("LED_PIN = %d", LED_PIN);
}

void loop() {
  unsigned long now = millis();

  // Uptime jede Sekunde
  if (now - lastUptime >= 1000) {
    lastUptime = now;
    Log::infof("Uptime: %lu ms", now);

    // LED toggeln + loggen
    led = !led;
    digitalWrite(LED_PIN, led ? HIGH : LOW);
    if (led) Log::success("Lampe AN");
    else     Log::warning("Lampe AUS");
  }
}
