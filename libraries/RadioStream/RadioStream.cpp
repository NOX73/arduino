#include <RadioStream.h>
#include <RF24.h>

RadioStream::RadioStream(RF24 *radio) {
  init(radio);
}

void RadioStream::init(RF24 *radio) {
  target = radio;
  reset_buffer();
  reset_wbuffer();
}

void RadioStream::reset_buffer() {
  for(int i=0;i<sizeof(buffer);i++){ buffer[i]=0; }
  buffer_pointer = 0;
}
void RadioStream::reset_wbuffer() {
  for(int i=0;i<sizeof(wbuffer);i++){ wbuffer[i]=0; }
  wbuffer_pointer = 0;
}

int RadioStream::available() {
  if(buffer_pointer >= recievedBuffer()){
    int a = target->available();
    if (a) {
      readFromRadio();
      return recievedBuffer();
    } else {
      return a;
    }
  } else {
    return recievedBuffer() - buffer_pointer;
  }

}

int RadioStream::recievedBuffer() {
  // if we want to send value which started from 0, we send 0xxxx..  and amount of bytes to read at the end
  char last = buffer[sizeof(buffer)-1];
  if(buffer[0] == 0 && last != 0) {
    return last;
  }
  int i = 0;
  uint8_t length = target->getPayloadSize();
  while(buffer[i] != 0 && i < length) i++;
  return i;
}

void RadioStream::readFromRadio() {
    reset_buffer();
    bool ok = target->read(buffer, sizeof(buffer));
}

int RadioStream::read() {
  if(buffer_pointer >= recievedBuffer()){
    readFromRadio();
  }

  int res = buffer[buffer_pointer];
  buffer_pointer++;

  return res;
}

void RadioStream::flush() {
  if(isBufferFree()){return;}

  beginWrite();
  bool ok = target->write( wbuffer , wbuffer_pointer );
  delay(50);
  endWrite();

  if(ok) { reset_wbuffer(); }
}

int RadioStream::peek() { return 0; }

size_t RadioStream::write(uint8_t val){
  if(wbuffer_pointer >= sizeof(wbuffer)){
    flush();

    if(isBufferFree()){
      wbuffer[wbuffer_pointer] = val;
      wbuffer_pointer++;
      return 1;
    } else {
      return 0;
    }

  } else {
    wbuffer[wbuffer_pointer] = val;
    wbuffer_pointer++;
    return 1;
  }
}

size_t RadioStream::write(char *str){
  size_t l = 0;
  while(*str != 0){
    write((uint8_t)*str);
    str++;
    l++;
  }
  return l;
}

bool RadioStream::isBufferFree() {
  return wbuffer_pointer == 0;
}

void RadioStream::beginWrite() {
  target->powerUp();
  target->stopListening();
  target->openWritingPipe(addr);
}
void RadioStream::endWrite() {
  target->startListening();
}

void RadioStream::setAddr(uint64_t val) {
  addr = val;
}

