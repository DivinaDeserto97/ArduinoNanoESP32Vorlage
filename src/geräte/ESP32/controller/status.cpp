#include "geräte/ESP32/controller/status.h"
#include "var.h"
#include "geräte/ESP32/config/wifi_config.h"

#include <Arduino.h>
#include <WiFi.h>

// ----------------------------------------------
// Startzeit vom Programm (setzen wir in main.cpp)
// ----------------------------------------------
extern unsigned long gStartMs;

// JSON String bauen (ohne ArduinoJson -> simpel & anfängerfreundlich)
void statusHandle(WebServer& server) {
  unsigned long now = millis();                    // aktuelle Zeit seit Boot
  unsigned long uptimeMs = now - gStartMs;         // Laufzeit seit Start

  // millis() Überlauf passiert nach ~49 Tagen (uint32)
  const unsigned long MILLIS_OVERFLOW_MS = 0xFFFFFFFFUL;

  bool wifiOk = wifiIsConnected();                 // WLAN Status
  String ip = wifiGetIp();                         // IP (oder 0.0.0.0)

  // JSON zusammenbauen
  String json = "{";
  json += "\"name\":\"" + String(DEVICE_NAME) + "\",";         // Gerätename
  json += "\"ip\":\"" + ip + "\",";                            // IP
  json += "\"start_ms\":" + String(gStartMs) + ",";            // Startzeitpunkt (ms)
  json += "\"uptime_ms\":" + String(uptimeMs) + ",";           // Laufzeit (ms)
  json += "\"millis_now\":" + String(now) + ",";               // aktueller millis()
  json += "\"millis_overflow_ms\":" + String(MILLIS_OVERFLOW_MS) + ","; // max millis
  json += "\"wifi_connected\":" + String(wifiOk ? "true" : "false");    // WLAN ok?
  json += "}";

  server.send(200, "application/json", json);      // Antwort senden
}
