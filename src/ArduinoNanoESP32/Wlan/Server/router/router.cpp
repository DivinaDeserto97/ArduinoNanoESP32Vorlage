#include "router.h"

#include "../controller/status_controller/status_controller.h"
#include "../controller/on_controller/on_controller.h"

#include "ArduinoNanoESP32/debug/logger.h"

namespace Router {

  void registerRoutes(WebServer& server) {

    // Route: /status
    server.on("/status", HTTP_GET, [&server]() {

      StatusController::handleStatus(server);
    });

    Log::info("[HTTP] Route registriert: /status");

    // Route: /on
    server.on("/on", HTTP_GET, [&server]() {

      OnController::handleOn(server);
    });

    Log::info("[HTTP] Route registriert: /on");

    // Route: /off
    server.on("/off", HTTP_GET, [&server]() {

      OnController::handleOff(server);
    });

    Log::info("[HTTP] Route registriert: /off");

    // Route: /pulse
    server.on("/pulse", HTTP_GET, [&server]() {

      OnController::handlePulse(server);
    });

    Log::info("[HTTP] Route registriert: /pulse");
  }

}
