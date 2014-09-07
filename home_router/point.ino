
void setupPoint() {
  setupDigitalPins();
  sendConnectedToRouter();
}

void sendConnectedToRouter() {
  char str[20];
  //from, message type
  Fmt.f(str,F("%d,connected;"), int(radio_num));

  sendLogToPoint(0, str);
}

void pointLoop() {
  cmdSource = cmdRadioMessenger;
  cmdRadioMessenger->feedinSerialData();

  cmdSource = cmdMessenger;
  cmdMessenger->feedinSerialData();

  Serial.flush();
  radioStream->flush();
}
