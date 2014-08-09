#ifndef Radio_Stream_h
#define Radio_Stream_h

#include "Stream.h"
#include "RF24.h"

#define RADIO_STREAM_PAYLOAD_SIZE 8

class RadioStream : public Stream
{
  private:
    RF24 *target;
    char buffer[RADIO_STREAM_PAYLOAD_SIZE];
    char wbuffer[RADIO_STREAM_PAYLOAD_SIZE];
    int buffer_pointer;
    int wbuffer_pointer;
    int addr;

    void init(RF24 *radio);
    void readFromRadio();
    int recievedBuffer();
    void reset_buffer();
    void reset_wbuffer();

    void beginWrite();
    void endWrite();

  public: 

    RadioStream(RF24 *radio);

    size_t write(uint8_t val);
    int read();
    void flush();
    int peek();
    int available();

    void setAddr(int addr);
};

#endif
