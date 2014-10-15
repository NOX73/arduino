#ifndef Radio_Stream_h
#define Radio_Stream_h

#include "Stream.h"
#include "RF24.h"

#define RADIO_STREAM_PAYLOAD_SIZE 16

class RadioStream : public Stream
{
  private:
    RF24 *target;
    char buffer[RADIO_STREAM_PAYLOAD_SIZE];
    char wbuffer[RADIO_STREAM_PAYLOAD_SIZE];
    int buffer_pointer;
    int wbuffer_pointer;
    uint64_t addr;

    void init(RF24 *radio);
    void readFromRadio();
    int recievedBuffer();

    void reset_buffer();
    void reset_wbuffer();

    bool isBufferFree();
    void beginWrite();
    void endWrite();

    //bool isFromZeroMessage();
    //bool shouldFlushMessageFromZero();

  public: 

    RadioStream(RF24 *radio);

    size_t write(uint8_t val);
    size_t write(char *str);

    int read();
    void flush();
    int peek();
    int available();


    //DEPRECATED use set_addr
    void setAddr(uint64_t addr);

    void set_addr(uint64_t addr);
};

#endif
