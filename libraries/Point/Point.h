#ifndef Point_h
#define Point_h

#include <JsonParser.h>
#include <JsonGenerator.h>
#include <Arduino.h>
#include <StoragePack.h>
#include <RadioPack.h>
#include <StreamPack.h>
#include <Defines.h>
#include "PointHandlers/Handlers.h"

#define POINT_SETUP_STATE    0

#define POINT_SEND_EVENT_EVERY 5000
#define POINT_SEND_SETUP_EVERY 10000


#define POINT_OUTGOING_LENGTH 10

using namespace ArduinoJson;

namespace Point {

  class Point {
    int state;
    int outgoing_pointer;
    char *outgoing[POINT_OUTGOING_LENGTH];

    private:
      void init();
      void setup_loop();
      void check_radio();
      void route_command(Parser::JsonObject);
      void check_event_request();
      void send_setup_request();
      void send_event_request();
      void outgoing_push(char*);

    public:
      void loop();
      Point();
  };

}
#endif


