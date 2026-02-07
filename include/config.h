#pragma once
#include <Arduino.h> // Arduino Grundfunktionen

// Gerätename für Logs und /status Antwort
static const char* DEVICE_NAME = "ServerEin";

// Wie oft WLAN geprüft wird (ms)
static const uint32_t WIFI_CHECK_INTERVAL_MS = 1000;

// Webserver Port (80 = normal im Browser ohne :Port)
static const uint16_t HTTP_PORT = 80;
