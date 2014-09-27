#define RADIO_SET_RETRIES1 15
#define RADIO_SET_RETRIES2 15
#define RADIO_PAYLOAD_SIZE 8

const uint64_t base_out_address = 0x0000000000LL;
const uint64_t base_in_address = 0x000000F000LL;

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
