#include <Arduino.h>                                  // Arduino Grundfunktionen
#include "ArduinoNanoESP32/debug/logger.h"            // Logger

#include "pins.h"                                     // Pins + Baudrate
#include "secrets.h"                                  // WLAN Daten
#include "config.h"                                   // DEVICE_NAME + Intervalle

#include "ArduinoNanoESP32/Wlan/wifi_manager.h"       // WLAN Manager
#include "ArduinoNanoESP32/Wlan/Server/server.h"      // HTTP Server

const int LED_PIN = PIN_LED;                          // LED Pin aus pins.h

unsigned long lastUptime = 0;                         // Zeitpunkt für 1-Sekunden-Takt
bool led = false;                                     // LED Zustand

void setup() {
  pinMode(LED_PIN, OUTPUT);                           // LED Pin als Ausgang setzen
  digitalWrite(LED_PIN, LOW);                         // LED am Anfang aus

  Serial.begin(SERIAL_BAUD);                          // Startet USB-Seriell mit Baudrate aus pins.h
  while (!Serial) { delay(10); }                      // Wartet bis PC verbunden ist

  Log::begin(true);                                   // Logger starten (mit Farben)

  Log::info("System gestartet");                      // Startmeldung
  Log::infof("Device: %s", DEVICE_NAME);              // Gerätename aus config.h
  Log::infof("Serial Baudrate: %lu", SERIAL_BAUD);    // Zeigt verwendete Baudrate
  Log::successf("LED_PIN = %d", LED_PIN);             // Zeigt LED Pin

  WifiManager::begin();                               // WLAN starten
}

void loop() {

  WifiManager::update();                              // WLAN prüfen + reconnect
  HttpServer::handle();                               // HTTP Server bedienen (/status)

  unsigned long now = millis();                       // aktuelle Laufzeit

  // jede Sekunde
  if (now - lastUptime >= 1000) {
    lastUptime = now;                                 // Referenzzeit aktualisieren
    Log::infof("Uptime: %lu ms", now);                // Uptime loggen

    led = !led;                                       // LED Zustand umschalten
    digitalWrite(LED_PIN, led ? HIGH : LOW);          // LED entsprechend setzen

    if (led) Log::success("Lampe AN");                // Log wenn LED an
    else     Log::warning("Lampe AUS");               // Log wenn LED aus
  }
}
