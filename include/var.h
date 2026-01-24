#pragma once
// Schutz gegen mehrfaches Einbinden

#include <Arduino.h>
// Damit wir millis() etc. nutzen können

// ----------------------------------------------
// Globale "Geräte-Infos"
// ----------------------------------------------

// Anzeigename vom Gerät (kommt in /status JSON)
static const char* DEVICE_NAME = "NanoESP32-Vorlage";

// Startzeitpunkt in Millisekunden seit Boot
static const unsigned long START_MS = 0; 
// Hinweis: START_MS setzen wir in main.cpp sauber, dort wird es "richtig" gebraucht.
