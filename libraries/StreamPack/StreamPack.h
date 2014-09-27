#ifndef StreamPack_h
#define StreamPack_h

#include <JsonParser.h>
#include <JsonGenerator.h>
#include <Stream.h>

#define STREAM_PACK_BUFFER 256

namespace StreamPack {
  using namespace ArduinoJson;

  void serialWriteLength(uint32_t);
  void serialWritePack(char*);
  void serialWritePack(char*, uint32_t);
  void serialReadPack(char*, uint32_t);
  uint32_t serialReadLength();
  char* serialReadPack();

  template<typename T>
  void printJsonObject(T object) {
    char buff[STREAM_PACK_BUFFER];
    uint32_t lenght = object.printTo(buff, sizeof(buff));
    serialWritePack(buff, lenght);
  }

}
#endif
