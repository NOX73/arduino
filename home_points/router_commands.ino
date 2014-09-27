using namespace ArduinoJson;
using namespace StreamPack;

#define ROUTER_COMMAND_INFO 1
#define ROUTER_COMMAND_LISTEN_EVENTS 2

void router_getInfo(Parser::JsonObject root) {

  Generator::JsonObject<1> radioObject;
  radioObject["lvl"] = radio.getPALevel();

  Generator::JsonObject<2> contentObject;
  contentObject["radio"] = radioObject;
  contentObject["mem"] = freeMemory();

  Generator::JsonObject<3> object;
  object["c"] = contentObject;
  object["id"] = long(root["id"]);
  object["t"] = MESSAGE_INFO;

  printJsonObject(object);
}

void router_listenEvents(Parser::JsonObject root) {
  radio_listenEvents();

  Generator::JsonObject<3> object;
  object["id"] = long(root["id"]);
  object["t"] = MESSAGE_RESP;
  object["r"] = true;

  printJsonObject(object);
}

void evalRouterCommand(Parser::JsonObject root) {
  long command = root["cmd"];

  switch (command) {
    case ROUTER_COMMAND_INFO: router_getInfo(root); break;
    case ROUTER_COMMAND_LISTEN_EVENTS: router_listenEvents(root); break;
  }

}

void sendRouterError(char *err) {
  Generator::JsonObject<1> object;
  object["err"] = err;

  printJsonObject(object);
}

void sendRouterDebug(char *str) {
  Generator::JsonObject<1> object;
  object["debug"] = str;

  printJsonObject(object);
}
