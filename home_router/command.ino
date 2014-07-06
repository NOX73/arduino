// Commands
enum {
  cmdHelp,
  cmdStatus,
  cmdSetLed,
  cmdSetRemoteLed,
  cmdSetRadioNum
};

void OnSetLedCmd() {
  bool ledOn = cmdSource->readBoolArg();

  ledOn ? ledTurnOn() : ledTurnOff();

  Log.Info("Led turn %s."CR, ledOn ? "on" : "off");
}

void OnUnknownCmd() {
  Log.Info("Unknown command %d."CR, cmdSource->CommandID());
}

void OnStatusCmd() {
  Log.Info("Led Status: %s."CR, led_val == HIGH ? "on" : "off");
  Log.Info("Radio Num: %d."CR, int(radio_num));
}

void OnHelpCmd() {
  Log.Info(CR);
  Log.Info("%d; - help"CR, cmdHelp);
  Log.Info("%d; - status"CR, cmdStatus);
  Log.Info("%d,<val>; - set led."CR, cmdSetLed);
  Log.Info("%d,<addr>,<val>; - set romote led"CR, cmdSetRemoteLed);
  Log.Info("%d,<val>; - Set radio number."CR, cmdSetRadioNum);
  Log.Info(CR);
}

void OnSetRadioNumCmd() {
  int val = cmdSource->readInt32Arg();
  radio_num = val;
  radio_num.save();
  Log.Info("Set radio_num to %d."CR, int(radio_num));
}

void setupCmd() {
  cmdMessenger.printLfCr();
  cmdRadioMessenger.printLfCr();

  cmdMessenger.attach(OnUnknownCmd);
  cmdMessenger.attach(cmdSetLed, OnSetLedCmd);
  cmdMessenger.attach(cmdStatus, OnStatusCmd);
  cmdMessenger.attach(cmdSetRemoteLed, OnSetRemoteLedCmd);
  cmdMessenger.attach(cmdHelp, OnHelpCmd);
  cmdMessenger.attach(cmdSetRadioNum, OnSetRadioNumCmd);
  
  cmdRadioMessenger.attach(OnUnknownCmd);  
  cmdRadioMessenger.attach(cmdHelp, OnHelpCmd);
  cmdRadioMessenger.attach(cmdSetLed, OnSetLedCmd); 
}

void OnSetRemoteLedCmd() {
  int addr = cmdSource->readInt16Arg();
  int ledVal = cmdSource->readInt16Arg();
  
  char val[] = {"2,0;"};
  val[2] = ledVal ? '1' : '0';
  sendStrToPoint(addr, val, sizeof(val));

  Log.Info("Remote Led on %d turn %s."CR, addr, ledVal ? "on" : "off");
}

