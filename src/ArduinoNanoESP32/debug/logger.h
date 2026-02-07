#pragma once                    // Verhindert, dass diese Datei mehrfach geladen wird (Schutz vor Fehlern)

#include <Arduino.h>           // Bindet die Arduino-Grundfunktionen ein (Serial, Pins, etc.)

namespace Log {                // Beginnt den Log-Namespace (organisiert alle Logger-Funktionen zusammen)

// Diese Liste definiert mögliche Log-Level (z.B. INFO, ERROR) für spätere Erweiterungen
enum class Level : uint8_t {
  DEBUG,                       // Für detaillierte Entwickler-Informationen
  INFO,                        // Für normale Statusmeldungen
  SUCCESS,                     // Für erfolgreiche Aktionen
  WARNING,                     // Für Warnungen (kein Fehler, aber beachten)
  ERROR                        // Für Fehler, die Probleme verursachen
};

// Diese Funktion startet den Logger und aktiviert oder deaktiviert Farben
void begin(bool enableColors = true);

// Diese Funktionen geben einfache Text-Nachrichten aus (ohne Variablen)

void debug(const char* msg);   // Gibt eine Debug-Nachricht aus (z.B. für Entwickler)
void info(const char* msg);    // Gibt eine Info-Nachricht aus (z.B. System gestartet)
void success(const char* msg); // Gibt eine Erfolgsmeldung aus (z.B. Verbindung OK)
void warning(const char* msg); // Gibt eine Warnmeldung aus (z.B. schwaches Signal)
void error(const char* msg);   // Gibt eine Fehlermeldung aus (z.B. SD-Karte fehlt)

// Diese Funktionen geben formatierte Nachrichten aus (mit Variablen wie printf)

void debugf(const char* fmt, ...);   // Debug-Nachricht mit Variablen
void infof(const char* fmt, ...);    // Info-Nachricht mit Variablen
void successf(const char* fmt, ...); // Erfolgsmeldung mit Variablen
void warningf(const char* fmt, ...); // Warnmeldung mit Variablen
void errorf(const char* fmt, ...);   // Fehlermeldung mit Variablen

} // namespace Log             // Ende des Log-Namespace
