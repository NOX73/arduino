#ifndef Point_h
#define Point_h

#include <JsonParser.h>
#include <JsonGenerator.h>
#include <Arduino.h>
#include <StoragePack.h>
#include <RadioPack.h>
#include <StreamPack.h>
#include <Defines.h>
//#include "PointHandlers/Handlers.h"

#define POINT_SETUP_STATE   0
#define POINT_INIT_STATE    1

#define POINT_SEND_EVENT_EVERY 5000
#define POINT_SEND_SETUP_EVERY 10000

using namespace ArduinoJson;

namespace Point {

  class Point {
    int state;
    int outgoing_pointer;

    private:
      void setup_loop();
      void check_radio();
      void route_command(Parser::JsonObject);
    public:
      void loop();
  };

}
#endif


