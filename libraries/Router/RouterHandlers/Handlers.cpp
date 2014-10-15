#include "Handlers.h"
#include "Router.h"
#include "RadioPack.h"
#include <MemoryFree.h>
#include <Defines.h>

namespace Router {
  namespace Handlers {

    void get_info(Parser::JsonObject root, int state, int rState) {
      Generator::JsonObject<3> radioObject;
      radioObject["lvl"] = RadioPack::pa_level();
      radioObject["rpd"] = RadioPack::test_rpd();
      radioObject["s"] = rState;

      Generator::JsonObject<3> contentObject;
      contentObject["radio"] = radioObject;
      contentObject["mem"] = freeMemory();
      contentObject["s"] = state;

      Generator::JsonObject<3> object;
      object["c"] = contentObject;
      object["id"] = long(root["id"]);
      object["t"] = MESSAGE_INFO;

      StreamPack::serialJsonObject(object);
    }

    void listen_events(Parser::JsonObject root) {
      RadioPack::listen_events();

      Generator::JsonObject<3> object;
      object["id"] = long(root["id"]);
      object["t"] = MESSAGE_RESP;
      object["r"] = true;

      StreamPack::serialJsonObject(object);
    }

    void new_point_event() {
      uint32_t point_number = RadioPack::read_event();

      Generator::JsonObject<1> contentObject;
      contentObject["from"] = int(point_number);

      Generator::JsonObject<3> object;
      object["id"] = 0;
      object["t"] = MESSAGE_POINT_EVENT;
      object["c"] = contentObject;

      StreamPack::serialJsonObject(object);
    }

    void print_error(char *str) {
      Generator::JsonObject<1> object;
      object["c"] = str;

      StreamPack::serialJsonObject(object);
    }


  }
} 
