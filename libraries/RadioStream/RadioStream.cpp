#include <RadioStream.h>

RadioStream::RadioStream(RF24 &radio)
{
  init(radio);
}

void RadioStream::flush()
{
}

int RadioStream::peek()
{
  return 0;
}

size_t RadioStream::write(uint8_t val){
  return 0;
}

void RadioStream::init(RF24 &radio)
{
  target = &radio;
}

int RadioStream::available()
{
  return target->available();
}

int RadioStream::read()
{
  int buff;
  bool ok = target->read(&buff, sizeof(buff));
  return buff;
}


