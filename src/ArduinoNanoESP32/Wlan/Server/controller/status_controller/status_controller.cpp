#include "status_controller.h"                        // Header dieser Datei

#include <WiFi.h>                                     // IP / Signalstärke vom WLAN

#include "config.h"                                   // DEVICE_NAME
#include "ArduinoNanoESP32/Wlan/wifi_manager.h"       // WifiManager Namespace

namespace StatusController {

  void handleStatus(WebServer& server) {

    // IP-Adresse: nur wenn WLAN verbunden ist, sonst 0.0.0.0
    String ip = WifiManager::isConnected()
      ? WiFi.localIP().toString()
      : "0.0.0.0";

    // Signalstärke: nur wenn WLAN verbunden ist, sonst 0
    int signal = WifiManager::isConnected()
      ? WiFi.RSSI()
      : 0;

    // JSON Text bauen
    String body = "{\n";

    body += "\"geraetename\":\"" + String(DEVICE_NAME) + "\",\n";
    body += "\"laufzeit_ms\":" + String(millis()) + ",\n";
    body += "\"wlan_status\":\"" + String(WifiManager::statusText()) + "\",\n";
    body += "\"ip_adresse\":\"" + ip + "\",\n";
    body += "\"signalstaerke_dbm\":" + String(signal) + "\n";

    body += "}\n";

    // JSON senden (Content-Type korrekt setzen)
    server.send(200, "application/json; charset=utf-8", body);
  }

}
