#include <Point.h>

namespace Point {

  Point::Point() {
    init();
  }

  void Point::init() {
    state = POINT_SETUP_STATE;
    outgoing_pointer = 0;
  }

  void Point::loop() {
    switch(state) {
      case POINT_SETUP_STATE: setup_loop(); break;
    }
  }

  void Point::setup_loop() {
    unsigned long last_event = millis();
    unsigned long last_setup = millis();

    while(state == POINT_INIT_STATE) {

      if(outgoing_pointer == 0 && last_setup - millis() > POINT_SEND_SETUP_EVERY) {
        send_setup_request();
        last_setup = millis();
      }

      if(last_event - millis() > POINT_SEND_EVENT_EVERY) {
        check_event_request();
        last_event = millis();
      }

      check_radio();
    }
  }

  void Point::check_event_request() {
    if(outgoing_pointer > 0) {
        send_event_request();
    }
  }

  void Point::check_radio() {
    if (RadioPack::available() > 4) {
      uint32_t length = StreamPack::radioReadLength();

      char pack[length+1];
      pack[length] = 0;

      StreamPack::radioReadPack(pack, length);

      Parser::JsonParser<JSON_PARSER_TOKENS> parser;
      Parser::JsonObject root = parser.parse(pack);

      if (root.success()) {
        route_command(root);
      } else {
        //TODO: send error to router
      }
    }


  }

  void Point::route_command(Parser::JsonObject root) {
    long command = root["t"];

    switch (command) {
      //case COMMAND_INFO: Handlers::get_info(root); break;
    }
  }

  void Point::send_event_request() {
    uint32_t num = StoragePack::point_num;
    StreamPack::writeEventFrom(num);
  }

  void Point::send_setup_request() {
    Generator::JsonObject<1> object;
    object["t"] = MESSAGE_POINT_SETUP;

    char *out = StreamPack::stringJsonObject(object);
    outgoing_push(out);
  }

  void Point::outgoing_push(char *out) {
    outgoing[outgoing_pointer] = out;
    outgoing_pointer ++;
  }

}
