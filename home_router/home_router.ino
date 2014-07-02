// Main

#include <CmdMessenger.h>
#include <EEPROMVar.h>
#include <EEPROMex.h>
#include <Logging.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>

#define LOGLEVEL LOG_LEVEL_DEBUG
#define RADIO_NUM 0
#define CE_PIN   9
#define CSN_PIN 10
#define SERIAL_BAUD 9600
#define LED 5

// Global variables
EEPROMVar<int> led_val(HIGH);
EEPROMVar<int> radio_num(RADIO_NUM);

RF24 radio(CE_PIN, CSN_PIN);

CmdMessenger cmdMessenger = CmdMessenger(Serial);

bool isRouter = false;

void setup() {
  Log.Init(LOGLEVEL, SERIAL_BAUD);

  setupStorage();
  setupRadio();
  setupCmd();
  setupLed();

  Log.Info("Arduino has started! Led status: %d"CR, int(led_val));
}

void loop() {
  isRouter ? routerLoop() : pointLoop();
}

