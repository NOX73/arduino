#ifndef StreamPack_h
#define StreamPack_h

#include <JsonParser.h>
#include <JsonGenerator.h>
#include <Stream.h>

#define STREAM_PACK_BUFFER 256

namespace StreamPack {

  extern Stream *serial;
  extern Stream *radio;

  using namespace ArduinoJson;

  void writeLength(Stream*, uint32_t);
  void writePack(Stream*, char*);
  void writePack(Stream*, char*, uint32_t);
  void readPack(Stream*, char*, uint32_t);
  uint32_t readLength(Stream*);

  void serialWriteLength(uint32_t);
  void serialWritePack(char*);
  void serialWritePack(char*, uint32_t);
  void serialReadPack(char*, uint32_t);
  uint32_t serialReadLength();

  void radioWriteLength(uint32_t);
  void radioWritePack(char*);
  void radioWritePack(char*, uint32_t);
  void radioReadPack(char*, uint32_t);
  uint32_t radioReadLength();

  template<typename T>
  void printJsonObject(Stream *stream, T object) {
    char buff[STREAM_PACK_BUFFER];
    uint32_t lenght = object.printTo(buff, sizeof(buff));
    writePack(stream, buff, lenght);
  }

  template<typename T>
  void serialJsonObject(T object) {
    printJsonObject(serial, object);
  }

  template<typename T>
  void radioJsonObject(T object) {
    printJsonObject(radio, object);
  }

  void setup(Stream*, Stream*);
  void flush();

}
#endif
