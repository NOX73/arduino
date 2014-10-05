using namespace ArduinoJson;

void router_setupLoop() {

  if (Serial.available() > 4) {
    uint32_t length = StreamPack::serialReadLength();
    char pack[length];

    StreamPack::serialReadPack(pack, length);
    StreamPack::serialWritePack(pack, length);

    state = ROUTER_WORK_STATE;
  }

}

void router_workLoop() {
  router_checkSerial();
  router_radioLoop();
}

void router_radioLoop() {
  switch (radioState) {
    case RADIO_STATE_EVENTS:
      router_listenEvents();
      break;
  }
}

void router_listenEvents() {

  if(radioStream.available() > 0){
    sendRouterDebug(">0");
  }

  if(radioStream.available() == 4) {

    sendRouterDebug("YES");

    uint32_t point_number = radio_ReadEvent();
    router_pointEvent(point_number);
  }
}

void router_checkSerial() {
  if (Serial.available() > 4) {
    uint32_t length = StreamPack::serialReadLength();

    char pack[length+1];
    pack[length] = 0;

    StreamPack::serialReadPack(pack, length);

    Parser::JsonParser<JSON_PARSER_TOKENS> parser;
    Parser::JsonObject root = parser.parse(pack);

    if (root.success()) {
      evalRouterCommand(root);
    } else {
      sendRouterError(pack);
    }
  }
}
