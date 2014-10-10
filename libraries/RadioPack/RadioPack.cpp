#include <SPI.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>

#define RADIO_SET_RETRIES1 15
#define RADIO_SET_RETRIES2 15
#define RADIO_PAYLOAD_SIZE 8

#define BASE_OUT_ADDRESS  0x0000000000LL
#define BASE_IN_ADDRESS   0x000000F000LL
#define EVENT_ADDRESS     0xF000000000LL

namespace RadioPack {
  RF24 *radio;

  void setup(RF24 *r) {
    radio = r;

    radio->begin();
    radio->setRetries(RADIO_SET_RETRIES1, RADIO_SET_RETRIES2);
    radio->setPayloadSize(RADIO_PAYLOAD_SIZE);
  }


  uint64_t out_address(int point_num) {
    return BASE_OUT_ADDRESS | point_num;
  }

  uint64_t in_address(int point_num) {
    return BASE_IN_ADDRESS | point_num;
  }

  void listen_events() {
    radio->stopListening();
    radio->openReadingPipe(1, EVENT_ADDRESS);
    radio->startListening();
  }

  void listen_point(int point_num) {
    radio->stopListening();
    radio->openReadingPipe(1, out_address(point_num));
    radio->startListening();
  }

  int available() {
    return radio->available();
  }

  int pa_level() {
    return radio->getPALevel();
  }

  bool test_rpd() {
    return radio->testRPD();
  }

}
