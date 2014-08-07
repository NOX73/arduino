// Commands
enum {
  cmdHelp,
  cmdStatus,
  cmdClearStorage,
  cmdSetDigital,
  cmdSetRemoteDigital,
  cmdSetRadioNum
};

void OnSetDigitalCmd() {
  int digital_num = cmdSource->readInt16Arg();
  bool ledOn = cmdSource->readBoolArg();

  ledOn ? digitalOn(digital_num) : digitalOff(digital_num);

  Log.Info(F("Digital #%d turn %s."CR), digital_num, ledOn ? "on" : "off");
}

void OnUnknownCmd() {
  Log.Info(F("Unknown command %d."CR), cmdSource->CommandID());
}

void OnStatusCmd() {  
  Log.Info(F("Led Status: %s."CR),  isDigitalOn(LED) ? "on" : "off");
  Log.Info(F("Relay Status: %s."CR),  isDigitalOn(RELAY) ? "on" : "off");
  Log.Info(F("Radio Num: %d."CR), int(radio_num));

  Log.Info(CR);  
  radio.printDetails();
  Log.Info(CR);
}

void OnHelpCmd() {
  Log.Info(CR);
  Log.Info(F("%d; - help"CR), cmdHelp);
  Log.Info(F("%d; - status"CR), cmdStatus);
  Log.Info(F("%d,<run setup>; - clear storage"CR), cmdClearStorage);
  Log.Info(F("%d,<num>,<val>; - set digital."CR), cmdSetDigital);
  Log.Info(F("\tLED - %d"CR), LED);
  Log.Info(F("\tRELAY - %d"CR), RELAY);
  Log.Info(F("%d,<addr>,<num>,<val>; - set romote digital"CR), cmdSetRemoteDigital);
  Log.Info(F("%d,<val>; - Set radio number."CR), cmdSetRadioNum);
  Log.Info(CR);
}

void OnSetRadioNumCmd() {
  int val = cmdSource->readInt32Arg();
  radio_num = val;
  radio_num.save();
  Log.Info("Set radio_num to %d."CR, int(radio_num));
}

void OnClearStorageCmd() {
  bool runSetup = cmdSource->readBoolArg();

  clearStorage();
  Log.Info(F("Storage has been cleaned."));

  if (runSetup) setupStorage();
}

void setupCmd() {
  
  cmdMessenger = new CmdMessenger(Serial);
  radioStream = new RadioStream(&radio);
  cmdRadioMessenger = new CmdMessenger(*radioStream);
  
  cmdSource = cmdMessenger;
  
  cmdMessenger->printLfCr();
  cmdRadioMessenger->printLfCr();

  cmdMessenger->attach(OnUnknownCmd);

  cmdMessenger->attach(cmdHelp, OnHelpCmd);
  cmdMessenger->attach(cmdStatus, OnStatusCmd);
  cmdMessenger->attach(cmdClearStorage, OnClearStorageCmd);

  cmdMessenger->attach(cmdSetDigital, OnSetDigitalCmd);
  cmdMessenger->attach(cmdSetRemoteDigital, OnSetRemoteDigitalCmd);
  cmdMessenger->attach(cmdSetRadioNum, OnSetRadioNumCmd);

  cmdRadioMessenger->attach(OnUnknownCmd);
  cmdRadioMessenger->attach(cmdSetDigital, OnSetDigitalCmd);
}

void OnSetRemoteDigitalCmd() {
  int addr = cmdSource->readInt16Arg();
  char digital_num = cmdSource->readCharArg();
  bool isOn = cmdSource->readBoolArg();

  // TODO: get 3 from cmdSetDigital
  char cmd[] = {'3',',', digital_num, ',', isOn ? '1' : '0',';',0};
  sendStrToPoint(addr, cmd, sizeof(cmd));

  Log.Info(F("Remote digital #%c on %d turn %s."CR), digital_num, addr, isOn ? "on" : "off");
}

