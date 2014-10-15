#ifndef RadioPack_h
#define RadioPack_h

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>

namespace RadioPack {
  extern RF24 *radio;

  void setup(RF24*);
  uint64_t out_address(int);
  uint64_t in_address(int);
  void listen_events();
  int pa_level();
  bool test_rpd();
  bool test_rpd();
  uint32_t read_event();

  int available();
}

#endif


