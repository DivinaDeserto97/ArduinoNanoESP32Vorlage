#include "geräte/ESP32/config/wifi_config.h"

// WLAN verbinden (mit Timeout)
bool wifiConnect(const char* ssid, const char* pass, unsigned long timeoutMs) {
  WiFi.mode(WIFI_STA);            // WLAN Client-Modus
  WiFi.begin(ssid, pass);         // Verbindungsversuch starten

  unsigned long start = millis(); // Startzeit merken

  while (WiFi.status() != WL_CONNECTED) {      // Solange nicht verbunden
    if (millis() - start > timeoutMs) {        // Timeout erreicht?
      return false;                            // Abbruch
    }
    delay(250);                                // Kurz warten (ok hier beim Connect)
  }

  return true; // verbunden
}

// WLAN verbunden?
bool wifiIsConnected() {
  return WiFi.status() == WL_CONNECTED;
}

// IP als String
String wifiGetIp() {
  if (!wifiIsConnected()) return String("0.0.0.0");
  return WiFi.localIP().toString();
}
