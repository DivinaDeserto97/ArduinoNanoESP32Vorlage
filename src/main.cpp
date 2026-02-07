#include <Arduino.h>                       // Grundfunktionen des Arduino (Pins, millis, etc.)
#include "ArduinoNanoESP32/debug/logger.h" // Dein eigenes Logger-System für Console-Ausgaben


#include "pins.h"                          // Die Pin Variabeln
#include "secrets.h"                       // Die geheimnisse

const int LED_PIN = PIN_LED;              // Speichert die Pin-Nummer aus der pins.h in der eingebauten LED

unsigned long lastUptime = 0;             // Speichert die Zeit des letzten Updates in Millisekunden
bool led = false;                         // Speichert den aktuellen Zustand der LED (AN oder AUS)

void setup() {
  pinMode(LED_PIN, OUTPUT);               // Setzt den LED-Pin als Ausgang (damit wir ihn steuern können)
  digitalWrite(LED_PIN, LOW);             // Schaltet die LED am Anfang aus

  Serial.begin(SERIAL_BAUD);              // Startet die USB-Serielle Verbindung mit der Baudrate aus pins.h
  while (!Serial) { delay(10); }          // Wartet, bis die Verbindung zum PC hergestellt ist

  Log::begin(true);                       // Startet den Logger (true = farbige Ausgabe im Terminal)

  Log::info("System gestartet");          // Gibt eine Info-Meldung aus: System wurde gestartet
  Log::successf("LED_PIN = %d", LED_PIN);// Gibt aus, welcher Pin für die LED verwendet wird
}

void loop() {
  unsigned long now = millis();           // Holt die aktuelle Laufzeit seit dem Start in Millisekunden

  // Prüft, ob 1000 ms (1 Sekunde) seit dem letzten Update vergangen sind
  if (now - lastUptime >= 1000) {

    lastUptime = now;                     // Speichert die aktuelle Zeit als neuen Referenzpunkt

    Log::infof("Uptime: %lu ms", now);   // Gibt die aktuelle Laufzeit im Terminal aus

    led = !led;                           // Wechselt den LED-Zustand (AN wird AUS, AUS wird AN)

    digitalWrite(LED_PIN, led ? HIGH : LOW); // Schaltet die LED entsprechend ein oder aus

    if (led)                              // Prüft, ob die LED jetzt an ist
      Log::success("Lampe AN");           // Gibt eine Erfolgsmeldung aus: LED ist an
    else                                  // Wenn LED aus ist
      Log::warning("Lampe AUS");          // Gibt eine Warnmeldung aus: LED ist aus
  }
}
