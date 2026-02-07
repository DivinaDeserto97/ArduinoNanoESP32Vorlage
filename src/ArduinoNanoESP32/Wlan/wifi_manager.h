#pragma once
#include <Arduino.h>   // Arduino Grundfunktionen

namespace WifiManager {

  // Startet WLAN-Verbindung
  void begin();

  // Muss regelmäßig in loop() aufgerufen werden
  void update();

  // Gibt true zurück, wenn WLAN verbunden ist
  bool isConnected();

  // Gibt WLAN Status als Text zurück
  const char* statusText();

}
