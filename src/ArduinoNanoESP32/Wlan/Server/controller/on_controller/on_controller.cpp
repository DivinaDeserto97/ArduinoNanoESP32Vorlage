#include "on_controller.h"

#include "pins.h"
#include "ArduinoNanoESP32/debug/logger.h"

namespace OnController {

  void handleOn(WebServer& server) {

    digitalWrite(PIN_RELAY, HIGH);

    Log::success("[HTTP] PIN_RELAY ON");

    server.send(200, "text/plain", "ON");
  }

  void handleOff(WebServer& server) {

    digitalWrite(PIN_RELAY, LOW);

    Log::warning("[HTTP] PIN_RELAY OFF");

    server.send(200, "text/plain", "OFF");
  }

  void handlePulse(WebServer& server) {

    Log::info("[HTTP] PIN_RELAY PULSE");

    digitalWrite(PIN_RELAY, HIGH);

    delay(200);

    digitalWrite(PIN_RELAY, LOW);

    server.send(200, "text/plain", "PULSE");
  }

}
