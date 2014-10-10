#include "Handlers.h"
#include "RadioPack.h"

namespace Router {
  namespace Handlers {

    void get_info() {
      Generator::JsonObject<3> radioObject;
      radioObject["lvl"] = RadioPack::getPALevel();
      radioObject["rpd"] = RadioPack::testRPD();
      radioObject["s"] = radioState;

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

    void listen_events() {
      RadioPack::listen_events();

      radioState = RADIO_STATE_EVENTS;

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


  }
} 
