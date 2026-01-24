#include <Arduino.h>

#include "config.h"
#include "pinout.h"

// =====================================================
// Mini-Logger (einfach, robust, anfängerfreundlich)
// =====================================================
void logLine(const String &msg) {
  Serial.println(msg);
}

// =====================================================
// Blink-Status
// =====================================================
bool ledState = false;
unsigned long lastBlinkMs = 0;

// =====================================================
// setup(): läuft genau 1x beim Start
// =====================================================
void setup() {
  // Serielle Schnittstelle starten (für Debug-Ausgaben)
  Serial.begin(SERIAL_BAUD);

  // Manche Boards brauchen ganz kurz Zeit, bis Serial bereit ist
  delay(200);

  logLine("=== Start: Vorlage-Projekt (Arduino Nano ESP32) ===");

  // Pin für LED als Ausgang setzen
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  logLine("Setup fertig.");
}

// =====================================================
// loop(): läuft endlos (Hauptprogramm)
// =====================================================
void loop() {
  const unsigned long now = millis();

  // --------- 1) LED-Blink ohne delay() (wichtig für spätere Erweiterungen)
  if (now - lastBlinkMs >= BLINK_INTERVAL_MS) {
    lastBlinkMs = now;

    ledState = !ledState;
    digitalWrite(PIN_LED, ledState ? HIGH : LOW);

    // Debug-Ausgabe
    logLine(String("LED: ") + (ledState ? "ON" : "OFF"));
  }

  // --------- 2) Platzhalter für spätere Module
  // Hier kannst du später Sensoren abfragen, Buttons lesen, etc.
  // Wichtig: möglichst ohne lange delay()-Aufrufe arbeiten.
}
