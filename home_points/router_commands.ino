using namespace ArduinoJson;
using namespace StreamPack;

#define ROUTER_COMMAND_INFO 1

void router_getInfo(Parser::JsonObject root) {
  int id = root["id"];

  Generator::JsonObject<8> object;
  object["mem"] = freeMemory();
  object["id"] = id;

  printJsonObject(object);
}

void evalRouterCommand(Parser::JsonObject root) {
  int command = root["cmd"];

  switch (command) {
    case ROUTER_COMMAND_INFO:
      router_getInfo(root);
      break;
  }

}

void sendRouterError(char *err) {
  Generator::JsonObject<8> object;
  object["err"] = err;

  printJsonObject(object);
}
