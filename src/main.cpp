#include <Arduino.h>
// Basis-Arduino-Funktionen wie millis(), pinMode(), digitalWrite()

#include "global/pins.h"
// Enthält die Definition von LED_PIN

#include "global/var.h"
// Enthält die Variable: unsigned long timer


void setup() {
  // setup() läuft genau EINMAL beim Start des Boards

  pinMode(LED_PIN, OUTPUT);
  // Setzt den LED-Pin als Ausgang
}


void loop() {
  // loop() läuft endlos immer wieder

  if (millis() - timer > 500) {
    // Prüft: Sind mehr als 500 Millisekunden vergangen?

    digitalWrite(LED_PIN, HIGH);
    // LED einschalten
  }

  if (millis() - timer > 1000) {
    // Prüft: Sind mehr als 1000 Millisekunden vergangen?

    digitalWrite(LED_PIN, LOW);
    // LED ausschalten

    timer = millis();
    // Aktuelle Zeit speichern → neuer Blink-Zyklus startet
  }

  if (timer > millis()) {
    // Schutz gegen Überlauf von millis()
    // Falls millis() wieder bei 0 beginnt

    timer = 0;
    // Timer zurücksetzen
  }
}
