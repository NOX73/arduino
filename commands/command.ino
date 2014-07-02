
// Commands
enum
{
  ledOn,
  ledOff
};

void cmdLedOn() {
  led_val = HIGH;
  led_val.save();
}

void cmdLedOff() {
  led_val = LOW;
  led_val.save();
}

void setupCmd() {
  cmdMessenger.printLfCr();
  cmdMessenger.attach(ledOn, cmdLedOn);
  cmdMessenger.attach(ledOff, cmdLedOn);
}
