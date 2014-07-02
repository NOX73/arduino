// Radio

enum {
  radio_role_router,
  radio_role_point
};

const uint64_t router_pipe = 0xF0F0F0F0E1LL;
const uint64_t point_pipes[1] = { 0xF0F0F0F0D2LL };

void setupRadio() {
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

int radioRole() {
  return radio_num == 0 ? radio_role_router : radio_role_point;
}

bool sendIntToPoint(int addr, int val) {
  radio.stopListening();

  radio.openWritingPipe(point_pipes[addr - 1]);

  Log.Info("Send to %d point value = %d"CR, addr, val);

  bool ok = radio.write( &val, sizeof(int) );
  radio.startListening();

  return ok;
}
