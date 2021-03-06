#include <EEPROMVar.h>
#include <EEPROMex.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>
#include <JsonParser.h>
#include <JsonGenerator.h>
#include <MemoryFree.h>
#include <StreamPack.h>
#include <RadioStream.h>

#define DEFAULT_POINT_NUM 0
#define CE_PIN 9
#define CSN_PIN 10
#define MAIN_LOOPS_COUNT 10
#define SERIAL_BAUD 115200
#define JSON_PARSER_TOKENS 32

EEPROMVar<bool> eeprom_init(false);
EEPROMVar<uint32_t> eeprom_point_num(DEFAULT_POINT_NUM);

RF24 radio(CE_PIN, CSN_PIN);

//typedef void(*FunctionPointer)(); FunctionPointer mainLoops[MAIN_LOOPS_COUNT];

#define IS_ROUTER 1

#define ROUTER_SETUP_STATE  0
#define ROUTER_WORK_STATE   1
#define POINT_INIT_STATE    2

#ifdef IS_ROUTER
int state = ROUTER_SETUP_STATE;
#else
int state = POINT_INIT_STATE;
#endif


#define RADIO_STATE_DISABLE 0
#define RADIO_STATE_EVENTS  1

RadioStream radioStream(&radio);
int radioState = RADIO_STATE_DISABLE;

#define MESSAGE_INFO          1
#define MESSAGE_RESP          2
#define MESSAGE_POINT_EVENT   3


void setup() {
  Serial.begin(SERIAL_BAUD);
  setupStorage();
  setupRadio();
  StreamPack::setup(&Serial, &radioStream);
}

void loop() {
  switch_loop(state);
}
