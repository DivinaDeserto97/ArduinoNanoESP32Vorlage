#pragma once
// Schutz gegen mehrfaches Einbinden

#define LED_PIN 13
// Die LED ist an Pin 13 angeschlossen

// Status-LED extern an D2 (NICHT die interne LED auf D13)
#define LED_SD_PIN 2

// Adafruit MicroSD (SPI) - deine aktuelle Verdrahtung:
#define SD_SCK_PIN   12   // CLK / SCK -> D12
#define SD_MOSI_PIN  11   // DI / MOSI -> D11
#define SD_MISO_PIN  10   // DO / MISO -> D10
#define SD_CS_PIN     9   // CS -> D9
#define SD_CD_PIN     8   // CD -> D8 (optional)