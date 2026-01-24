# Vorlage – Arduino Nano ESP32 (PlatformIO)

## Ziel
Ein ausbaubares Anfänger-Vorlageprojekt:

- LED blinkt ohne `delay()` (non-blocking)
- Serielle Debug-Ausgaben über USB
- Konfiguration & Pins zentral in `include/`
- Saubere Basis für spätere Erweiterungen (Sensoren, WLAN, etc.)

---

## Voraussetzungen

- Linux (z. B. Linux Mint)
- VS Code
- PlatformIO Extension (VS Code)
- Board: **Arduino Nano ESP32**
- USB-Kabel (**Datenkabel**, kein reines Ladekabel)

---

## Projekt öffnen

1. VS Code öffnen
2. Ordner `Vorlage/` öffnen
3. Warten, bis PlatformIO das Projekt geladen hat

---

## Upload (Programm auf das Board laden)

### Variante A: Über VS Code (empfohlen)
1. Board per USB verbinden
2. In VS Code links auf **PlatformIO**
3. Klick auf **Upload**

### Variante B: Über Terminal
```bash
pio run -t upload
```

---

## Serieller Monitor (Debug-Ausgaben ansehen)

```bash
pio device monitor
```

⚠️ Wichtig:
- Die Baudrate muss mit `Serial.begin(115200)` im Code übereinstimmen.

---

## Projektstruktur erklärt

```text
Vorlage/
├─ platformio.ini        → Zentrale PlatformIO-Konfiguration
├─ README.md             → Diese Datei (Erklärung & Anleitung)
├─ src/
│  └─ main.cpp           → Hauptprogramm (setup & loop)
├─ include/
│  ├─ config.h           → Einstellungen (z.B. Blink-Intervall)
│  └─ pinout.h           → Alle Pins zentral definiert
└─ lib/
   └─ README.md           → Platz für eigene Module/Bibliotheken
```

---

## Idee hinter dieser Vorlage

- **Anfängerfreundlich**: alles ist kommentiert
- **Erweiterbar**: neue Module können sauber ergänzt werden
- **Ohne delay()**: wichtig für spätere Sensoren & WLAN
- **Lernprojekt**: Fehler & Warnungen sind absichtlich aktiviert

---

## Nächste mögliche Erweiterungen

- Button-Eingang
- Sensor-Modul (Temperatur, Licht, etc.)
- WLAN-Grundstruktur (ESP32)
- Logging-Modul
- Konfigurierbares Blink-Intervall

---

Viel Spass beim Lernen & Basteln 🚀