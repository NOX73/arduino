void setupRouter() {
}

void routerLoop() {
  cmdSource = cmdRadioMessenger;
  cmdRadioMessenger->feedinSerialData();

  cmdSource = cmdMessenger;
  cmdMessenger->feedinSerialData();
  
  Serial.flush();
  radioStream->flush();
}
