#include <EEPROMVar.h>
#include <EEPROMex.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>

#include <JsonParser.h>
#include <JsonGenerator.h>
#include <MemoryFree.h>
#include <Defines.h>
#include <RadioStream.h>

#include <RadioPack.h>
#include <StreamPack.h>
#include <StoragePack.h>

#define CE_PIN 9
#define CSN_PIN 10

#define SERIAL_BAUD 115200
#define JSON_PARSER_TOKENS 32

//#define IS_ROUTER 1

RF24 radio(CE_PIN, CSN_PIN);
RadioStream radioStream(&radio);

void setup() {
  Serial.begin(SERIAL_BAUD);
  RadioPack::setup(&radio);
  StoragePack::setup();
  StreamPack::setup(&Serial, &radioStream);

  role_setup();
}

#ifdef IS_ROUTER

#include <Router.h>

Router::Router router;

void loop() {
  router.loop();
}

void role_setup() {
}

#else

#include <Point.h>

Point::Point point;

void loop() {
  point.loop();
}

void role_setup() {
}

#endif
