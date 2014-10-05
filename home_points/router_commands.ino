using namespace ArduinoJson;

#define ROUTER_COMMAND_INFO 1
#define ROUTER_COMMAND_LISTEN_EVENTS 2

void router_getInfo(Parser::JsonObject root) {

  Generator::JsonObject<3> radioObject;
  radioObject["lvl"] = radio.getPALevel();
  radioObject["rpd"] = radio.testRPD();
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

void router_listenEvents(Parser::JsonObject root) {
  radio_listenEvents();
  
  radioState = RADIO_STATE_EVENTS;

  Generator::JsonObject<3> object;
  object["id"] = long(root["id"]);
  object["t"] = MESSAGE_RESP;
  object["r"] = true;

  StreamPack::serialJsonObject(object);
}

void router_pointEvent(uint32_t point_number) {
  Generator::JsonObject<1> contentObject;
  contentObject["from"] = int(point_number);

  Generator::JsonObject<3> object;
  object["id"] = 0;
  object["t"] = MESSAGE_POINT_EVENT;
  object["c"] = contentObject;

  StreamPack::serialJsonObject(object);
}

void evalRouterCommand(Parser::JsonObject root) {
  long command = root["t"];

  switch (command) {
    case ROUTER_COMMAND_INFO: router_getInfo(root); break;
    case ROUTER_COMMAND_LISTEN_EVENTS: router_listenEvents(root); break;
  }

}

void sendRouterError(char *str) {
  sendRouterDebug(str);
}

void sendRouterDebug(char *str) {
  Generator::JsonObject<1> object;
  object["d"] = str;

  StreamPack::serialJsonObject(object);
}
