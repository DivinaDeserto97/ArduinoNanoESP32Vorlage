#include "logger.h"   // Bindet die passende Header-Datei ein, damit alle Logger-Funktionen bekannt sind
#include <stdarg.h>   // Wird benötigt, um Funktionen mit variabler Anzahl an Parametern zu ermöglichen (printf-Stil)

namespace Log {       // Beginnt den Log-Namespace, damit alle Logger-Funktionen logisch gruppiert sind

static bool g_colors = true;  // Speichert, ob farbige Ausgabe im Terminal aktiviert ist oder nicht

// ANSI Farb-Codes für farbige Ausgabe im Terminal
static const char* COL_RESET  = "\033[0m";  // Setzt die Farbe zurück auf Standard
static const char* COL_RED    = "\033[31m"; // Farbe Rot für Fehler
static const char* COL_GREEN  = "\033[32m"; // Farbe Grün für Erfolg
static const char* COL_YELLOW = "\033[33m"; // Farbe Gelb für Warnungen
static const char* COL_BLUE   = "\033[34m"; // Farbe Blau für Infos
static const char* COL_CYAN   = "\033[36m"; // Farbe Cyan für Debug

// Diese Funktion druckt den Prefix wie z.B. [INFO] oder [ERROR]
static void prefix(const char* color, const char* tag) {

  if (g_colors && color)          // Prüft, ob Farben aktiviert sind
    Serial.print(color);          // Setzt die gewünschte Farbe

  Serial.print(tag);              // Druckt den Text-Tag wie [INFO]

  if (g_colors)
    Serial.print(COL_RESET);      // Setzt die Farbe wieder zurück

  Serial.print(' ');              // Fügt ein Leerzeichen nach dem Tag hinzu
}

// Diese Funktion druckt eine formatierte Zeile mit Variablen (wie printf)
static void vprintLine(const char* color, const char* tag, const char* fmt, va_list args) {

  prefix(color, tag);             // Druckt zuerst den Prefix mit Farbe und Tag

  char buf[192];                  // Erstellt einen Text-Puffer, um die Nachricht zu speichern

  vsnprintf(buf, sizeof(buf), fmt, args); // Formatiert den Text mit Variablen in den Puffer

  Serial.println(buf);            // Gibt den fertigen Text im Terminal aus
}

// Diese Funktion startet den Logger und aktiviert oder deaktiviert Farben
void begin(bool enableColors) {
  g_colors = enableColors;       // Speichert, ob Farben verwendet werden sollen
}

/* --- Einfache Funktionen ohne Variablen --- */

// Debug-Nachricht ausgeben
void debug(const char* msg) {
  prefix(COL_CYAN, "[DEBUG]");   // Prefix mit Cyan-Farbe und [DEBUG]
  Serial.println(msg);           // Nachricht ausgeben
}

// Info-Nachricht ausgeben
void info(const char* msg) {
  prefix(COL_BLUE, "[INFO ]");   // Prefix mit Blau-Farbe und [INFO]
  Serial.println(msg);           // Nachricht ausgeben
}

// Erfolgsmeldung ausgeben
void success(const char* msg) {
  prefix(COL_GREEN, "[OK   ]");  // Prefix mit Grün-Farbe und [OK]
  Serial.println(msg);           // Nachricht ausgeben
}

// Warnmeldung ausgeben
void warning(const char* msg) {
  prefix(COL_YELLOW, "[WARN ]"); // Prefix mit Gelb-Farbe und [WARN]
  Serial.println(msg);           // Nachricht ausgeben
}

// Fehlermeldung ausgeben
void error(const char* msg) {
  prefix(COL_RED, "[ERROR]");    // Prefix mit Rot-Farbe und [ERROR]
  Serial.println(msg);           // Nachricht ausgeben
}

/* --- Funktionen mit Variablen (printf-Stil) --- */

// Debug-Nachricht mit Variablen ausgeben
void debugf(const char* fmt, ...) {

  va_list a;                     // Erstellt eine Variable für die zusätzlichen Parameter

  va_start(a, fmt);              // Startet das Einlesen der zusätzlichen Parameter

  vprintLine(COL_CYAN, "[DEBUG]", fmt, a); // Gibt die formatierte Debug-Nachricht aus

  va_end(a);                     // Beendet die Verarbeitung der Parameter
}

// Info-Nachricht mit Variablen ausgeben
void infof(const char* fmt, ...) {

  va_list a;
  va_start(a, fmt);

  vprintLine(COL_BLUE, "[INFO ]", fmt, a); // Gibt die formatierte Info-Nachricht aus

  va_end(a);
}

// Erfolgsmeldung mit Variablen ausgeben
void successf(const char* fmt, ...) {

  va_list a;
  va_start(a, fmt);

  vprintLine(COL_GREEN, "[OK   ]", fmt, a); // Gibt die formatierte Erfolgs-Nachricht aus

  va_end(a);
}

// Warnmeldung mit Variablen ausgeben
void warningf(const char* fmt, ...) {

  va_list a;
  va_start(a, fmt);

  vprintLine(COL_YELLOW, "[WARN ]", fmt, a); // Gibt die formatierte Warn-Nachricht aus

  va_end(a);
}

// Fehlermeldung mit Variablen ausgeben
void errorf(const char* fmt, ...) {

  va_list a;
  va_start(a, fmt);

  vprintLine(COL_RED, "[ERROR]", fmt, a); // Gibt die formatierte Fehler-Nachricht aus

  va_end(a);
}

} // namespace Log  // Ende des Log-Namespace
