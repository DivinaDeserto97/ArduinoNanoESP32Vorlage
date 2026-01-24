#include <Arduino.h>
#include <WebServer.h>

#include "geheimnisse.h"
#include "pins.h"
#include "var.h"


#include "geräte/ESP32/config/wifi_config.h"
#include "geräte/ESP32/router/mainRouter.h"

// ----------------------------------------------
// Globale Startzeit (wird im Status-Controller benutzt)
// ----------------------------------------------
unsigned long gStartMs = 0;

// WebServer auf Port 80
WebServer server(80);

void setup() {
  Serial.begin(115200);                // Serielle Ausgabe starten
  delay(200);                          // Mini-Wartezeit für Serial

  gStartMs = millis();                 // Startzeitpunkt merken

  pinMode(LED_PIN, OUTPUT);            // LED Pin als Ausgang
  digitalWrite(LED_PIN, LOW);          // LED aus

  Serial.println("Boot: Starte WLAN...");

  // WLAN verbinden (10 Sekunden Timeout)
  bool ok = wifiConnect(WIFI_SSID, WIFI_PASS, 10000);

  if (ok) {
    Serial.print("WLAN OK, IP: ");
    Serial.println(wifiGetIp());
    digitalWrite(LED_PIN, HIGH);       // LED an = WLAN ok (nur als Signal)
  } else {
    Serial.println("WLAN FEHLER (Timeout)");
    digitalWrite(LED_PIN, LOW);        // LED aus = WLAN nicht ok
  }

  // Routen registrieren
  registerRoutes(server);

  // Server starten
  server.begin();
  Serial.println("HTTP Server gestartet: /status");
}

void loop() {
  server.handleClient();               // HTTP Anfragen bearbeiten
}
