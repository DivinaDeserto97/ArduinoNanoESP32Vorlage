#include "geräte/ESP32/router/mainRouter.h"
#include "geräte/ESP32/controller/ArduinoNanoESP32/status/status.h"

// ----------------------------------------------
// Hier wird nur "verdrahtet":
// /status -> statusHandle(server)
// ----------------------------------------------

void registerRoutes(WebServer& server) {
  server.on("/status", HTTP_GET, [&server]() { // Route /status GET
    statusHandle(server);                      // Controller aufrufen
  });

  // Später:
  // server.on("/gpio", HTTP_POST, ...);
}
