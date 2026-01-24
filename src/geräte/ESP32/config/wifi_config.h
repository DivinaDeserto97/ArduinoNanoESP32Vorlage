#pragma once
// Schutz gegen mehrfaches Einbinden

#include <Arduino.h>
#include <WiFi.h>

// ----------------------------------------------
// WLAN Funktionen (Config)
// ----------------------------------------------

// WLAN verbinden (true = verbunden)
bool wifiConnect(const char* ssid, const char* pass, unsigned long timeoutMs);

// WLAN verbunden?
bool wifiIsConnected();

// IP als String (z.B. "192.168.1.50")
String wifiGetIp();
