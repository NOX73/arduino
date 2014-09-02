
void setupPoint() {
  setupDigitalPins();
}

void pointLoop() {
  cmdSource = cmdRadioMessenger;
  cmdRadioMessenger->feedinSerialData();

  cmdSource = cmdMessenger;
  cmdMessenger->feedinSerialData();
  
  Serial.flush();
  radioStream->flush();
}
