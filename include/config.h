#pragma once

// =====================================================
// CONFIG (hier stellst du Verhalten ein)
// =====================================================

// Wie oft soll die LED blinken? (Millisekunden)
static const unsigned long BLINK_INTERVAL_MS = 500;

// Serial Logging
static const unsigned long SERIAL_BAUD = 115200;

// Feature-Schalter (später erweiterbar)
// Beispiel: WLAN später aktivieren -> auf 1 setzen
#define FEATURE_WIFI 0
