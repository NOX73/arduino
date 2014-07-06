#include <RadioStream.h>
#include <RF24.h>

RadioStream::RadioStream(RF24 *radio) {
  init(radio);
}

void RadioStream::init(RF24 *radio) {
  target = radio;
  buffer_pointer = sizeof(buffer);
}

int RadioStream::available() {

  if(buffer_pointer >= recievedBuffer()){
    int a = target->available();
    if(a){
      readFromRadio();
      return recievedBuffer();
    }else{
      return a;
    }
  } else {
    return recievedBuffer() - buffer_pointer;
  }

}

int RadioStream::recievedBuffer() {
  int i=0;
  while(buffer[i] != 0) i++;

  return i;
}

void RadioStream::readFromRadio() {
    bool ok = target->read(buffer, sizeof(buffer));
    buffer_pointer = 0;
}

int RadioStream::read() {
  if(buffer_pointer >= recievedBuffer()){
    readFromRadio();
  }

  int res = buffer[buffer_pointer];

  buffer_pointer++;

  return res;
}

void RadioStream::flush() { }
int RadioStream::peek() { return 0; }
size_t RadioStream::write(uint8_t val){ return 0; } 

