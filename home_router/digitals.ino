EEPROMVar<int> *getDigital(int digital_num) {
  return &digitals[digital_num - DIGITAL_SHIFT];
}

void digitalInitDefaults() {
  EEPROMVar<int> *ledD = getDigital(LED);
  EEPROMVar<int> *relayD = getDigital(RELAY);

  ledD->operator=(HIGH);
  relayD->operator=(HIGH);

  ledD->save();
  relayD->save();
}

void digitalOn(int digital_num) {
  EEPROMVar<int> *d = getDigital(digital_num);
  d->operator=(HIGH);
  d->save();
  digitalWrite(digital_num, *d);
}

void digitalOff(int digital_num) {
  EEPROMVar<int> *d = getDigital(digital_num);
  d->operator=(LOW);
  d->save();
  digitalWrite(digital_num, *d);
}

bool isDigitalOn(int digital_num) {
  return *getDigital(digital_num) == HIGH;
}


void setupDigitalPins() {
  pinMode(LED, OUTPUT);
  pinMode(RELAY, OUTPUT);

  EEPROMVar<int> *ledD = getDigital(LED);
  EEPROMVar<int> *relayD = getDigital(RELAY);

  ledD->restore();
  relayD->restore();

  digitalWrite(LED, *ledD);
  digitalWrite(RELAY, *relayD);
}
