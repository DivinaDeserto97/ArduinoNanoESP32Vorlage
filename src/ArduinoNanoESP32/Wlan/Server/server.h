#pragma once
#include <Arduino.h>

namespace HttpServer {

  // startet den HTTP Server
  void begin();

  // verarbeitet HTTP Anfragen
  void handle();

}
