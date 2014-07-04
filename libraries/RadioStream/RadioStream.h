#ifndef Radio_Stream_h
#define Radio_Stream_h

#include "Stream.h"
#include "RF24.h"

class RadioStream : public Stream 
{
  private:
    RF24 *target;

    void init(RF24 &radio);

  public: 

    RadioStream(RF24 &radio);

    size_t write(uint8_t val);
    int read();
    void flush();
    int peek();
    int available();
};

#endif
