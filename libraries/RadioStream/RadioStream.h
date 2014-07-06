#ifndef Radio_Stream_h
#define Radio_Stream_h

#include "Stream.h"
#include "RF24.h"

#define PAYLOAD_SIZE 8

class RadioStream : public Stream
{
  private:
    RF24 *target;
    char buffer[PAYLOAD_SIZE];
    int buffer_pointer;

    void init(RF24 *radio);
    void readFromRadio();
    int recievedBuffer();

  public: 

    RadioStream(RF24 *radio);

    size_t write(uint8_t val);
    int read();
    void flush();
    int peek();
    int available();
};

#endif
