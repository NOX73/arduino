#include <StreamPack.h>

namespace StreamPack {
  using namespace ArduinoJson;

  Stream *serial;
  RadioStream *radio;

  void writeLength(Stream *stream, uint32_t length) {
    char length_bytes[] = { length & 0xFF, (length >> 8) & 0xFF, (length >> 16) & 0xFF, (length >> 24) & 0xFF };
    stream->write(length_bytes, 4);
  }

  void writePack(Stream *stream, char pack[]) {
    serialWriteLength(sizeof(pack) - 1);
    stream->write(pack);
  }

  void writePack(Stream *stream, char pack[], uint32_t length) {
    writeLength(stream, length);
    stream->write(pack, length);
  }

  void readPack(Stream *stream, char *b, uint32_t length) {
    for(uint32_t i = 0; i < length; i++ ){
      while(stream->available() == 0) delay(10);
      b[i] = stream->read();
    }
  }

  uint32_t readLength(Stream *stream) {
    char length_bytes[4] = { 0, 0, 0, 0 };

    stream->readBytes(length_bytes, 4);
    uint32_t length = (uint32_t(length_bytes[3]) << 24) | (uint32_t(length_bytes[2]) << 16) | (uint32_t(length_bytes[1]) << 8) | uint32_t(length_bytes[0]);

    return length;
  }




  void serialWriteLength(uint32_t length){
    writeLength(serial, length);
  }

  void serialWritePack(char *pack) {
    writePack(serial, pack);
  }

  void serialWritePack(char *pack, uint32_t length) {
    writePack(serial, pack, length);
  }

  void serialReadPack(char *pack, uint32_t length) {
    readPack(serial, pack, length);
  }

  uint32_t serialReadLength() {
    return readLength(serial);
  }



  void radioWriteLength(uint32_t length){
    writeLength(radio, length);
  }

  void radioWritePack(char *pack) {
    writePack(radio, pack);
  }

  void radioWritePack(char *pack, uint32_t length) {
    writePack(radio, pack, length);
  }

  void radioReadPack(char *pack, uint32_t length) {
    readPack(radio, pack, length);
  }

  uint32_t radioReadLength() {
    return readLength(radio);
  }

  void setup(Stream *s, RadioStream *r) {
    serial = s;
    radio = r;
  }

  void flush() {
    serial->flush();
    radio->flush();
  }

  void writeEventFrom(uint32_t from) {
    uint64_t addr = RadioPack::events_addr();

    radio->set_addr(addr);

    radioWriteLength(from);

    radio->flush();
  }

}
