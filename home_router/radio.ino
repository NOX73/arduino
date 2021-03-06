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
  radio.setPayloadSize(RADIO_PAYLOAD_SIZE);

  if ( isRouter ) {
    radio.openReadingPipe(1, router_pipe);
  } else {
    radio.openWritingPipe(router_pipe);
    radio.openReadingPipe(1, point_pipes[radio_num - 1]);
  }

  radio.startListening();
}

void beginSend(int addr) {
  radio.powerUp(); // write function call powerDown
  radio.stopListening();
  radio.openWritingPipe(resolveRadioAddr(addr));
}

uint64_t resolveRadioAddr(int addr) {
  return addr == 0 ? router_pipe : point_pipes[addr - 1];
}

void endSend() {
  radio.startListening();
}

int radioRole() {
  return radio_num == 0 ? radio_role_router : radio_role_point;
}

void sendResetToPoint(int addr) {
  radioStream->setAddr(resolveRadioAddr(addr));
  radioStream->write(";");
}

void sendLogToPoint(int addr, char *str) {
  sendResetToPoint(addr);
  
  cmdRadioMessenger->sendCmdStart(cmdLogStr);
  cmdRadioMessenger->sendCmdEscArg(str);
  cmdRadioMessenger->sendCmdEnd();

  Log.Debug(F("Send to %d log '%s'"CR), addr, str);
}


//Does not used
bool sendStrToPoint(int addr, char *str) {
  signed int sizeofval = 0;
  for (; * (str + sizeofval) != 0; sizeofval++) {}

  bool ok = true;
  bool localOk;

  for (int i = 0; i < sizeofval; i += RADIO_PAYLOAD_SIZE) {
    beginSend(addr);

    int count = min(RADIO_PAYLOAD_SIZE, sizeofval - i);

    char *strFrom = str + i;

    Log.Debug(F("Sending to %d string=%s count=%d sizeofval=%d i=%d PSIZE=%d ..."CR), addr, strFrom, count, sizeofval, i, RADIO_PAYLOAD_SIZE);
    for (int j = 1; j < RADIO_WRITE_RETRY; j++) {

      localOk = radio.write( strFrom , count );

      if (localOk) {
        Log.Debug(F("Chunk sended."CR));
        break;
      }

      Log.Debug(F("Retry #%d to send chunk ... "CR), j);
      delay(j * 1000);


    }

    ok &= localOk;
  }

  endSend();
  return ok;
}
