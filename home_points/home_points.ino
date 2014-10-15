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
//#include <StreamPack.h>
#include <RadioStream.h>

#include <RadioPack.h>
#include <StreamPack.h>
#include <StoragePack.h>

#define CE_PIN 9
#define CSN_PIN 10

#define SERIAL_BAUD 115200
#define JSON_PARSER_TOKENS 32

//EEPROMVar<bool> eeprom_init(false);
//EEPROMVar<uint32_t> eeprom_point_num(DEFAULT_POINT_NUM);

//typedef void(*FunctionPointer)(); FunctionPointer mainLoops[MAIN_LOOPS_COUNT];

#define IS_ROUTER 1

//#ifdef IS_ROUTER
//int state = ROUTER_SETUP_STATE;
//#else
//int state = POINT_INIT_STATE;
//char *outgoing[POINT_OUTGOING_LENGTH];
//int outgoing_pointer = 0;
//#endif

RF24 radio(CE_PIN, CSN_PIN);
RadioStream radioStream(&radio);

//int radioState = RADIO_STATE_DISABLE;

void setup() {
  Serial.begin(SERIAL_BAUD);
  RadioPack::setup(&radio);
  StoragePack::setup();
  StreamPack::setup(&Serial, &radioStream);
}

#ifdef IS_ROUTER

#include <Router.h>

Router::Router router;

void loop() {
  router.loop();
}

#else

#include <Point.h>

Point::Point point;

void loop() {
  point.loop();
}

#endif
