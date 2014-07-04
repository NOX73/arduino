// Main

#include <CmdMessenger.h>
#include <EEPROMVar.h>
#include <EEPROMex.h>
#include <Logging.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24_config.h>
#include <RF24.h>

#include <RadioStream.h>

#define LOGLEVEL LOG_LEVEL_DEBUG
#define RADIO_NUM 0
#define CE_PIN   9
#define CSN_PIN 10
#define SERIAL_BAUD 9600
#define LED 5

// Global variables
EEPROMVar<bool> eeprom_init(false);
EEPROMVar<int> led_val(HIGH);
EEPROMVar<int> radio_num(RADIO_NUM);

RF24 radio(CE_PIN, CSN_PIN);

CmdMessenger cmdMessenger = CmdMessenger(Serial);
RadioStream radioStream = RadioStream(radio);
CmdMessenger cmdRadioMessenger = CmdMessenger(radioStream);

bool isRouter = false;

void setup() {
  Log.Init(LOGLEVEL, SERIAL_BAUD);

  setupStorage();
  setupRadio();
  setupCmd();
  setupLed();
  
  isRouter ? setupRouter() : setupPoint();

  Log.Info("Arduino has started with role %s!"CR, isRouter ? "router" : "point");
}

void loop() {
  isRouter ? routerLoop() : pointLoop();
}

