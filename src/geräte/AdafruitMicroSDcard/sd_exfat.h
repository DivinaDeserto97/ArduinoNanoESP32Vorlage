#pragma once
#include <Arduino.h>

// SD (exFAT) initialisieren
bool sdExfatBegin();

// Einmalig prüfen (setzt LED sofort)
void sdExfatLedCheckOnce();

// Regelmäßig prüfen (intern mit Timer, z.B. 1x pro Sekunde)
void sdExfatLedCheckTick();
