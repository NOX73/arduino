#include <CmdMessenger.h>
#include <EEPROMVar.h>
#include <EEPROMex.h>

int led = LED_BUILTIN;
EEPROMVar<int> led_val(HIGH);

void setup() {
  
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  setupCmd();
  setupStorage();
  
}

void loop() {
  
  CmdMessenger.feedinSerialData();
  digitalWrite(led, led_val);

}
