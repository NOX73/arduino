#include <EEPROMVar.h>
#include <EEPROMex.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>

#define DEFAULT_POINT_NUM 0
#define CE_PIN 9
#define CSN_PIN 10
#define MAIN_LOOPS_COUNT 10
#define SERIAL_BAUD 115200

EEPROMVar<bool> eeprom_init(false);
EEPROMVar<int> eeprom_point_num(DEFAULT_POINT_NUM);

RF24 radio(CE_PIN, CSN_PIN);

typedef void(*FunctionPointer)();
FunctionPointer mainLoops[MAIN_LOOPS_COUNT];

void setup() {
  setupSerial();
  setupStorage();
  setupRadio();
  setupMainLoops();
}
void loop() {
  FunctionPointer fp = mainLoops[getMainLoopState()];
  (*fp)();
}

int getMainLoopState() {
  return 0;
}

