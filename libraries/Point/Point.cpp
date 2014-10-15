#include <Point.h>

namespace Point {

  void Point::loop() {
    switch(state) {
      case POINT_SETUP_STATE: setup_loop(); break;
    }
  }

  void Point::setup_loop() {
    uint32_t num = StoragePack::point_num;
    unsigned long last_event = millis();
    unsigned long last_setup = millis();

    while(state == POINT_INIT_STATE) {

      if(outgoing_pointer == 0 && last_setup - millis() > POINT_SEND_SETUP_EVERY) {
        //Handlers::send_setup_request();
        last_setup = millis();
      }

      if(last_event - millis() > POINT_SEND_EVENT_EVERY) {
        //Handlers::send_event_request();
        last_event = millis();
      }

      check_radio();
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


}
