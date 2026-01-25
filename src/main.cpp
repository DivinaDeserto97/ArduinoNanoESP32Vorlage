#include <Arduino.h>

/* ============================================================
   ANSI-Farben (funktionieren im PlatformIO Monitor / Terminal)
   ============================================================ */
#define COL_RESET  "\033[0m"
#define COL_RED    "\033[31m"
#define COL_GREEN  "\033[32m"
#define COL_YELLOW "\033[33m"
#define COL_BLUE   "\033[34m"
#define COL_WHITE  "\033[37m"

/* ============================================================
   Debug-Makros
   ============================================================ */
#define LOG_INFO(msg)  Serial.println(COL_BLUE   "[INFO] "  msg COL_RESET)
#define LOG_WARN(msg)  Serial.println(COL_YELLOW "[WARN] "  msg COL_RESET)
#define LOG_ERROR(msg) Serial.println(COL_RED    "[ERR ] "  msg COL_RESET)

/* ============================================================
   Hardware
   ============================================================ */
const int LED_PIN = LED_BUILTIN;

/* ============================================================
   Zeiten (ms)
   ============================================================ */
const unsigned long LED_ON_AFTER   = 500;   // LED an nach 0.5 s
const unsigned long CYCLE_LENGTH   = 1000;  // Zyklus 1 s
const unsigned long UPTIME_INTERVAL = 1000; // Uptime-Ausgabe

/* ============================================================
   Variablen
   ============================================================ */
unsigned long cycleStart = 0;
unsigned long lastUptimePrint = 0;
bool ledState = false;

/* ============================================================
   Hilfsfunktionen
   ============================================================ */
void setLed(bool on) {
  if (ledState == on) return;   // nur bei Änderung

  ledState = on;
  digitalWrite(LED_PIN, on ? HIGH : LOW);

  Serial.print("[LED] ");
  Serial.println(on ? COL_GREEN "AN" COL_RESET
                    : COL_RED   "AUS" COL_RESET);
}

/* ============================================================
   setup()
   ============================================================ */
void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  while (!Serial) { delay(10); }

  Serial.println();
  Serial.println(COL_WHITE "=== Nano ESP32 Debug Monitor gestartet ===" COL_RESET);
  Serial.print(COL_WHITE "LED_PIN: " COL_RESET);
  Serial.println(LED_PIN);

  cycleStart = millis();
  lastUptimePrint = millis();

  LOG_INFO("Setup abgeschlossen");
}

/* ============================================================
   loop()
   ============================================================ */
void loop() {
  unsigned long now = millis();

  /* ---- Uptime ---- */
  if (now - lastUptimePrint >= UPTIME_INTERVAL) {
    lastUptimePrint = now;

    Serial.print(COL_WHITE "[UPTIME] " COL_RESET);
    Serial.print(now);
    Serial.println(" ms");
  }

  /* ---- LED-Zyklus ---- */
  unsigned long inCycle = now - cycleStart;

  if (inCycle >= LED_ON_AFTER && inCycle < CYCLE_LENGTH) {
    setLed(true);
  }

  if (inCycle >= CYCLE_LENGTH) {
    setLed(false);
    cycleStart = now;
    LOG_WARN("Zyklus reset");
  }
}
