#pragma once

#include <WebServer.h>

namespace OnController {

  void handleOn(WebServer& server);

  void handleOff(WebServer& server);

  void handlePulse(WebServer& server);

}
