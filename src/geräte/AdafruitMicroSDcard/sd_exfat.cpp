#include <Arduino.h>
#include <SPI.h>
#include <SdFat.h>

#include "pins.h"
#include "geräte/AdafruitMicroSDcard/sd_exfat.h"

// ----------------------------
// SdFat exFAT Objekte
// ----------------------------
static SdFs sd;                   // SdFat "Filesystem"-Objekt (kann FAT/exFAT)
static SPIClass spiSD(FSPI);      // eigenes SPI (deine Pins)

// ----------------------------
// Status / Timer
// ----------------------------
static bool gSdReady = false;     // true = SD initialisiert
static unsigned long gLastCheckMs = 0;

// ----------------------------
// Welche Datei soll gefunden werden?
// Tipp: Umlaute können manchmal zicken.
// Wenn Probleme: benenne Datei zu "/geraet.json" um.
// ----------------------------
static const char* SD_TEST_FILE = "/Gerät.json";

// ----------------------------
// SD starten (exFAT fähig)
// ----------------------------
bool sdExfatBegin() {
  // CD ist optional – wenn du den Pin nutzt:
  pinMode(SD_CD_PIN, INPUT_PULLUP);               // Karten-Detect (optional)

  // SPI mit deinen Pins starten
  spiSD.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);

  // SdFat SPI-Config
  SdSpiConfig cfg(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(10), &spiSD);

  // SD mounten
  gSdReady = sd.begin(cfg);

  Serial.print("SD init: ");
  Serial.println(gSdReady ? "OK" : "FAIL");

  return gSdReady;
}

// ----------------------------
// Einmal prüfen (Datei da?) -> LED setzen
// ----------------------------
void sdExfatLedCheckOnce() {
  if (!gSdReady) {
    digitalWrite(LED_SD_PIN, LOW);
    Serial.println("SD check: SD not ready");
    return;
  }

  bool exists = sd.exists(SD_TEST_FILE);

  digitalWrite(LED_SD_PIN, exists ? HIGH : LOW);

  Serial.print("SD check once: ");
  Serial.print(SD_TEST_FILE);
  Serial.print(" -> ");
  Serial.println(exists ? "FOUND (LED D2 ON)" : "MISSING (LED D2 OFF)");
}

// ----------------------------
// Regelmäßig prüfen (1x pro Sekunde)
// ----------------------------
void sdExfatLedCheckTick() {
  const unsigned long intervalMs = 1000;          // alle 1 Sekunde

  unsigned long now = millis();
  if (now - gLastCheckMs < intervalMs) return;
  gLastCheckMs = now;

  // Wenn SD nie initialisiert wurde / fehlgeschlagen ist:
  if (!gSdReady) {
    digitalWrite(LED_SD_PIN, LOW);
    return;
  }

  bool exists = sd.exists(SD_TEST_FILE);
  digitalWrite(LED_SD_PIN, exists ? HIGH : LOW);

  // Debug nur kurz (damit der Monitor nicht zugespammt wird)
  Serial.print("SD tick: ");
  Serial.println(exists ? "FOUND" : "MISSING");
}
