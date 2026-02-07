#include "server.h"

#include <WebServer.h>                          // HTTP Server

#include "config.h"
#include "ArduinoNanoESP32/debug/logger.h"
#include "router/router.h"
#include "../wifi_manager.h"

static WebServer server(HTTP_PORT);             // erstellt Server auf Port 80

static bool started = false;                    // merkt ob Server läuft

namespace HttpServer {

  void begin() {

    if(started)
      return;

    Router::registerRoutes(server);             // registriert alle URLs

    server.begin();                             // startet Server

    started = true;

    Log::success("[HTTP] Server gestartet");
  }

  void handle() {

    if(!WifiManager::isConnected())
      return;

    if(!started)
      begin();

    server.handleClient();                      // verarbeitet Anfragen
  }

}
