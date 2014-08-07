// Radio

enum {
  radio_role_router,
  radio_role_point
};

const uint64_t router_pipe = 0xF0F0F0F0E1LL;
const uint64_t point_pipes[1] = { 0xF0F0F0F0D2LL };

void radioInitDefaults() {
  radio_num = RADIO_NUM;
  radio_num.save();
}

void setupRadio() {
  radio_num.restore();

  isRouter = radioRole() == radio_role_router;

  radio.begin();
  radio.setRetries(15, 15);
  radio.setPayloadSize(8);

  if ( isRouter )
  {
    radio.openReadingPipe(1, router_pipe);
  }
  else
  {
    radio.openWritingPipe(router_pipe);
    radio.openReadingPipe(1, point_pipes[radio_num - 1]);
  }


  radio.startListening();
}

void beginSend(int addr) {
  radio.stopListening();
  radio.openWritingPipe(point_pipes[addr - 1]);
}

void endSend() {
  radio.startListening();
}

int radioRole() {
  return radio_num == 0 ? radio_role_router : radio_role_point;
}

bool sendIntToPoint(int addr, int val) {
  beginSend(addr);

  Log.Info(F("Send to %d point int value = %d"CR), addr, val);

  bool ok = radio.write( &val, sizeof(int) );

  endSend();
  return ok;
}

bool sendCharToPoint(int addr, char val) {
  beginSend(addr);

  Log.Info(F("Send to %d point char value = %c with size %d"CR), addr, val, sizeof(val));

  bool ok = radio.write( &val, sizeof(val) );

  endSend();
  return ok;
}

bool sendStrToPoint(int addr, char val[], int sizeofval) {
  beginSend(addr);

  Log.Info(F("Send to %d point string value = %s with size %d."CR), addr, val, sizeofval);

  bool ok = radio.write( val, sizeofval );

  endSend();
  return ok;
}
