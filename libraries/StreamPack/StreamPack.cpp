#include <JsonParser.h>
#include <JsonGenerator.h>
#include <StreamPack.h>
#include <Arduino.h>

namespace StreamPack {
  using namespace ArduinoJson;

  Stream *stream = &Serial;

  void serialWriteLength(uint32_t length) {
    char length_bytes[] = { length & 0xFF, (length >> 8) & 0xFF, (length >> 16) & 0xFF, (length >> 24) & 0xFF };
    stream->write(length_bytes, 4);
  }

  void serialWritePack(char pack[]) {
    serialWriteLength(sizeof(pack) - 1);
    stream->write(pack);
  }

  void serialWritePack(char pack[], uint32_t length) {
    serialWriteLength(length);
    stream->write(pack, length);
  }

  void serialReadPack(char *b, uint32_t length) {
    for(uint32_t i = 0; i < length; i++ ){
      while(stream->available() == 0) delay(10);
      b[i] = stream->read();
    }
  }

  uint32_t serialReadLength() {
    char length_bytes[4] = { 0, 0, 0, 0 };

    stream->readBytes(length_bytes, 4);
    uint32_t length = (uint32_t(length_bytes[3]) << 24) | (uint32_t(length_bytes[2]) << 16) | (uint32_t(length_bytes[1]) << 8) | uint32_t(length_bytes[0]);

    return length;
  }

  char* serialReadPack() {
    uint32_t length = serialReadLength();
    char *b = new char[length];
    serialReadPack(b, length);
    return b;
  }

}
