// Commands
enum {
  cmdHelp,
  cmdStatus,
  cmdSetLed,
  cmdSetRemoteLed,
  cmdSetRadioNum
};

void OnSetLedCmd() {
  bool ledOn = cmdMessenger.readBoolArg();

  ledOn ? ledTurnOn() : ledTurnOff();

  Log.Info("Led turn %s."CR, ledOn ? "on" : "off");
}

void OnUnknownCmd() {
  Log.Info("Unknown command."CR);
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
  int val = cmdMessenger.readInt32Arg();
  radio_num = val;
  radio_num.save();
  Log.Info("Set radio_num to %d."CR, int(radio_num));
}

void setupCmd() {
  cmdMessenger.printLfCr();

  cmdMessenger.attach(OnUnknownCmd);
  cmdMessenger.attach(cmdSetLed, OnSetLedCmd);
  cmdMessenger.attach(cmdStatus, OnStatusCmd);
  cmdMessenger.attach(cmdSetRemoteLed, OnSetRemoteLedCmd);
  cmdMessenger.attach(cmdHelp, OnHelpCmd);
  cmdMessenger.attach(cmdSetRadioNum, OnSetRadioNumCmd);
}

void OnSetRemoteLedCmd() {
  int addr = cmdMessenger.readInt16Arg();
  int ledVal = cmdMessenger.readInt16Arg();
  
  char message[] = {"0;"CR};

  for (int i = 0; i < 1; i++) {
    bool ok = sendIntToPoint(addr, ledVal);
    Log.Info("%d Sending result: %s"CR, i , ok ? "ok" : "fail");
    delay(3000);
  }

}

