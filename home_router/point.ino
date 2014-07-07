
void setupPoint() {
}

void pointLoop() {

  cmdSource = &cmdRadioMessenger;
  cmdRadioMessenger.feedinSerialData();

  cmdSource = &cmdMessenger;
  cmdMessenger.feedinSerialData();

}
