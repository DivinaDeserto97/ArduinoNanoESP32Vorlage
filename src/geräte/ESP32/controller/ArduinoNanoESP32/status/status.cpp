#include "geräte/ESP32/controller/ArduinoNanoESP32/status/status.h"
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
  String json = "{\n";

  json += "  \"arduinoNanoESP32\": {\n";
  json += "    \"name\": \"" + String(DEVICE_NAME) + "\",\n";
  json += "    \"ip\": \"" + ip + "\",\n";
  json += "    \"start_ms\": " + String(gStartMs) + ",\n";
  json += "    \"uptime_ms\": " + String(uptimeMs) + ",\n";
  json += "    \"millis_now\": " + String(now) + ",\n";
  json += "    \"millis_overflow_ms\": " + String(MILLIS_OVERFLOW_MS) + ",\n";
  json += "    \"wifi_connected\": " + String(wifiOk ? "true" : "false") + "\n";
  json += "  },\n";

  json += "  \"AdafruitMicroSDcard\": {\n";
  json += "    \"mounted\": false\n";   // Platzhalter
  json += "    \"free_bytes\": 0,\n";   // Platzhalter
  json += "    \"used_bytes\": 0\n";   // Platzhalter
  json += "  }\n";

  json += "}";


  server.send(200, "application/json", json);      // Antwort senden
}
