#ifndef Router_h
#define Router_h

#define ROUTER_SETUP_STATE 0
#define ROUTER_WORK_STATE 1

#include <JsonParser.h>
#include <JsonGenerator.h>
#include "Handlers/Handlers.h"

using namespace ArduinoJson;

namespace Router {

  class Router {

    int state;

    private:
      void init();
      void setup();
      void setup_loop();
      void work_loop();
      void check_serial();
      void check_radio();
      void listen_events();
      void route_command(Parser::JsonObject root);

    public:
      void loop();
      Router();

  };

}


#endif
