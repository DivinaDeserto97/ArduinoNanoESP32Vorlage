#include "wifi_manager.h"                       // eigener Header

#include <WiFi.h>                               // WLAN Bibliothek

#include "secrets.h"                            // WLAN Name und Passwort
#include "config.h"                             // Gerätename
#include "ArduinoNanoESP32/debug/logger.h"     // Logger

namespace WifiManager {

  // mögliche Zustände des WLAN
  enum class State {
    NO_WIFI,
    CONNECTING,
    CONNECTED
  };

  static State state = State::NO_WIFI;          // aktueller Zustand

  static unsigned long lastCheck = 0;           // Zeitpunkt letzter Check

  void begin() {

    WiFi.mode(WIFI_STA);                        // ESP32 arbeitet als Client

    WiFi.setHostname(DEVICE_NAME);              // setzt Gerätenamen

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);       // startet Verbindung

    state = State::CONNECTING;

    Log::infof("[WIFI] Verbinde mit %s", WIFI_SSID);
  }

  void update() {

    unsigned long now = millis();

    // nur alle 1000 ms prüfen
    if(now - lastCheck < 1000)
      return;

    lastCheck = now;

    if(WiFi.status() == WL_CONNECTED) {

      if(state != State::CONNECTED) {

        state = State::CONNECTED;

        Log::successf(
          "[WIFI] Verbunden! IP: %s",
          WiFi.localIP().toString().c_str()
        );
      }

    }
    else {

      if(state == State::CONNECTED) {

        Log::warning("[WIFI] Verbindung verloren");
      }

      state = State::CONNECTING;
    }
  }

  bool isConnected() {

    return WiFi.status() == WL_CONNECTED;
  }

  const char* statusText() {

    switch(state) {

      case State::CONNECTED: return "CONNECTED";

      case State::CONNECTING: return "CONNECTING";

      default: return "NO_WIFI";
    }
  }

}
