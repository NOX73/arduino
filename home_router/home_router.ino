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

#include "printf.h"

#define LOGLEVEL LOG_LEVEL_DEBUG
#define RADIO_NUM 0
#define CE_PIN 9
#define CSN_PIN 10
#define SERIAL_BAUD 57600
#define RADIO_PAYLOAD_SIZE 8
#define RADIO_WRITE_RETRY 5

// Global variables
EEPROMVar<bool> eeprom_init(false);
EEPROMVar<int> radio_num(RADIO_NUM);

// Digital
#define LED 3
#define RELAY 4
// Digital number in array is (number - DIGITAL_SHIFT)
#define DIGITAL_SHIFT 3
EEPROMVar<int> digitals[2] = {HIGH, HIGH};

RF24 radio(CE_PIN, CSN_PIN);

//CmdMessenger cmdMessenger = CmdMessenger(Serial);
//RadioStream radioStream = RadioStream(&radio);
//CmdMessenger cmdRadioMessenger = CmdMessenger(radioStream);

//CmdMessenger *cmdSource = &cmdMessenger;

CmdMessenger *cmdMessenger;
CmdMessenger *cmdRadioMessenger;
RadioStream *radioStream;

CmdMessenger *cmdSource;

bool isRouter = false;

void setup() {
  
  Log.Init(LOGLEVEL, SERIAL_BAUD);
  printf_begin();

  setupStorage();
  setupRadio();
  setupCmd();
  setupDigitalPins();
  
  isRouter ? setupRouter() : setupPoint();

  Log.Info(F("Arduino has started with role %s!"CR), isRouter ? "router" : "point");
}

void loop() {
  isRouter ? routerLoop() : pointLoop();
}

