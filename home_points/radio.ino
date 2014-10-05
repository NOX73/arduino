#define RADIO_SET_RETRIES1 15
#define RADIO_SET_RETRIES2 15
#define RADIO_PAYLOAD_SIZE 8

const uint64_t base_out_address = 0x0000000000LL;
const uint64_t base_in_address = 0x000000F000LL;

const uint64_t event_address = 0xF000000000LL;

void setupRadio() {
  eeprom_point_num.restore();

  radio.begin();
  radio.setRetries(RADIO_SET_RETRIES1, RADIO_SET_RETRIES2);
  radio.setPayloadSize(RADIO_PAYLOAD_SIZE);
}

uint64_t getOutAddress() {
  return base_out_address | (int(eeprom_point_num));
}

uint64_t getInAddress() {
  return base_in_address | (int(eeprom_point_num));
}

uint64_t getEventAddress() {
  return event_address;
}

void radio_listenEvents() {
  radio.stopListening();
  radio.openReadingPipe(1, getEventAddress());
  radio.startListening();
}

uint32_t radio_ReadEvent() {
  return StreamPack::radioReadLength();
}

void radio_sendEventFrom(uint32_t point_num) {
  StreamPack::radioWriteLength(point_num);
  StreamPack::flush();
}
