#include <Router.h>
#include <StreamPack.h>
#include <RadioPack.h>
#include "Handlers/Handlers.cpp"

#define JSON_PARSER_TOKENS 32

using namespace ArduinoJson;

namespace Router {

  Router::Router() {
    init();
  }

  void Router::init() {}

  void Router::loop() {
    switch(state) {
      case ROUTER_SETUP_STATE: setup_loop(); break;
      case ROUTER_WORK_STATE: work_loop(); break;
    }
  }

  void Router::setup_loop() {
      if (Serial.available() > 4) {
        setup();
        state = ROUTER_WORK_STATE;
      }
  }

  void Router::setup() {
    uint32_t length = StreamPack::serialReadLength();
    char pack[length];

    StreamPack::serialReadPack(pack, length);
    StreamPack::serialWritePack(pack, length);
  }

  void Router::work_loop() {
    check_serial();
    check_radio();
  }

  void Router::check_serial() {
    if (Serial.available() > 4) {
      uint32_t length = StreamPack::serialReadLength();

      char pack[length+1];
      pack[length] = 0;

      StreamPack::serialReadPack(pack, length);

      Parser::JsonParser<JSON_PARSER_TOKENS> parser;
      Parser::JsonObject root = parser.parse(pack);

      if (root.success()) {
        route_command(root);
      } else {
        Handlers::print_error(pack);
      }
    }
  }

  void Router::route_command(Parser::JsonObject root) {
    long command = root["t"];

    switch (command) {
      case COMMAND_INFO: Handlers::get_info(root); break;
      case COMMAND_LISTEN_EVENTS: Handlers::listen_events(root); break;
    }

  }

  void Router::check_radio() {
    switch (radioState) {
      case RADIO_STATE_EVENTS:
        check_events();
        break;
    }
  }

  void Router::check_events(){
    if(RadioPack::available() > 0) {
      uint32_t point_number = radio_ReadEvent();
      Handlers::new_point_event(point_number);
    }
  }


}
