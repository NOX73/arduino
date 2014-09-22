#define RADIO_SET_RETRIES1 15
#define RADIO_SET_RETRIES2 15
#define RADIO_PAYLOAD_SIZE 8

void setupRadio() {
  eeprom_point_num.restore();

  radio.begin();
  radio.setRetries(RADIO_SET_RETRIES1, RADIO_SET_RETRIES2);
  radio.setPayloadSize(RADIO_PAYLOAD_SIZE);
}

