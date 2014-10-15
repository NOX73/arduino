#ifndef Router_h
#define Router_h

#define ROUTER_SETUP_STATE  0
#define ROUTER_WORK_STATE   1

#define ROUTER_RADIO_DISABLE  0
#define RADIO_STATE_EVENTS    1

#include <JsonParser.h>
#include <JsonGenerator.h>
#include "RouterHandlers/Handlers.h"

using namespace ArduinoJson;

namespace Router {

  class Router {

    int state;
    int radioState;

    private:
      void init();
      void setup();
      void setup_loop();
      void work_loop();
      void check_serial();
      void check_radio();
      void check_events();
      void listen_events(Parser::JsonObject);
      void route_command(Parser::JsonObject);

      int get_state();
      void set_state(int);
      int get_radioState();
      void set_radioState(int);

    public:

      void loop();
      Router();

  };

}


#endif
