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
  int i=0;
  while(buffer[i] != 0 && i < target->getPayloadSize()) i++;
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
    beginWrite();
    ok = radio.write( wbuffer , wbuffer_pointer );
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


bool isBufferFree() {
  return wbuffer_pointer == 0;
}

void beginWrite() {
  target->powerUp();
  target->stopListening();
  target->openWritingPipe(addr);
}
void endWrite() {
  target->startListening();
}

void setAddr(int val) {
  addr = val;
}

