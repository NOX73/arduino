// Commands
enum {
  cmdHelp,
  
  cmdStatus,
  cmdClearStorage,
  cmdSetRadioNum,
  cmdSetDigital,
  
  cmdSendStrToPoint,
  cmdLogStr,
  
  cmdSendDigital
  
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
  Log.Info(F("Led Status:\t %s."CR),  isDigitalOn(LED) ? "on" : "off");
  Log.Info(F("Relay Status:\t %s."CR),  isDigitalOn(RELAY) ? "on" : "off");
  Log.Info(F("Radio Num:\t %d."CR), int(radio_num));
  Log.Info(F("Free memory:\t %d."CR), freeMemory());

  Log.Info(CR);  
  radio.printDetails();
  Log.Info(CR);
}

void OnHelpCmd() {
  Log.Info(CR);
  Log.Info(F("%d;\t\t\t - help"CR), cmdHelp);
  Log.Info(F("%d;\t\t\t - status"CR), cmdStatus);
  Log.Info(F("%d,<run setup>;\t\t - clear storage"CR), cmdClearStorage);
  Log.Info(F("%d,<val>;\t\t - Set radio number."CR), cmdSetRadioNum);
  Log.Info(F("%d,<num>,<val>;\t\t - set digital."CR), cmdSetDigital);
  Log.Info(F("\tLED - %d"CR), LED);
  Log.Info(F("\tRELAY - %d"CR), RELAY);
  Log.Info(F("%d,<addr>,<string>;\t - send string to address"CR), cmdSendStrToPoint);
  Log.Info(F("%d,<string>;\t\t - output string to console"CR), cmdLogStr);
  Log.Info(F("%d,<addr>,<num>;\t\t - send digital value to addr."), cmdSendDigital);

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
  cmdRadioMessenger->attach(OnUnknownCmd);

  cmdMessenger->attach(cmdHelp, OnHelpCmd);
  cmdMessenger->attach(cmdStatus, OnStatusCmd);
  cmdMessenger->attach(cmdClearStorage, OnClearStorageCmd);
  cmdMessenger->attach(cmdSetRadioNum, OnSetRadioNumCmd);
  cmdMessenger->attach(cmdSetDigital, OnSetDigitalCmd);

  cmdMessenger->attach(cmdSendStrToPoint, OnSendStrToPointCmd);
  cmdMessenger->attach(cmdLogStr, OnLogStrCmd);
  cmdMessenger->attach(cmdSendDigital, OnSendDigitalCmd);

  cmdRadioMessenger->attach(cmdSetDigital, OnSetDigitalCmd);  
  cmdRadioMessenger->attach(cmdSendStrToPoint, OnSendStrToPointCmd);
  cmdRadioMessenger->attach(cmdLogStr, OnLogStrCmd);
  
  cmdRadioMessenger->attach(cmdSendDigital, OnSendDigitalCmd);

}

void OnSendDigitalCmd() {
  int addr = cmdSource->readInt16Arg();
  int num = cmdSource->readInt16Arg();
  
  char val = bitRead(PORTD,num);
  
  char str[20];
  // from, message type, pin number, value
  Fmt.f(str,F("%d,digital,%d,%d;"), int(radio_num), num, val);
  
  sendLogToPoint(addr, str);
  
  Log.Info(F("Send to %d digital #%d = %d."CR), addr, num, val);
}

void OnLogStrCmd() {
  char *str = cmdSource->readStringArg();
  cmdSource->unescape(str);
  Log.Info(F(">>>:%s"CR), str);
}

void OnSendStrToPointCmd() {
  int addr = cmdSource->readInt16Arg();
  char *str = cmdSource->readStringArg();
  cmdSource->unescape(str);
  
  radioStream->setAddr(resolveRadioAddr(addr));
  radioStream->write(str);
  
  Log.Info(F("Sended String To Point: %d Cmd: '%s' Result: %T"CR), addr, str, true);
}

