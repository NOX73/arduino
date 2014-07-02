// Commands
enum {
  cmdHelp,
  cmdStatus,
  cmdSetLed,
  cmdSetRemoteLed
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
  Log.Info("%d; - help\n\r%d; - status\n\r%d,<val>; - set led\n\r%d,<addr>,<val> - set romote led"CR, cmdHelp, cmdStatus, cmdSetLed, cmdSetRemoteLed);
}

void setupCmd() {
  cmdMessenger.printLfCr();

  cmdMessenger.attach(OnUnknownCmd);
  cmdMessenger.attach(cmdSetLed, OnSetLedCmd);
  cmdMessenger.attach(cmdStatus, OnStatusCmd);
  cmdMessenger.attach(cmdSetRemoteLed, OnSetRemoteLedCmd);
  cmdMessenger.attach(cmdHelp, OnHelpCmd);
}

void OnSetRemoteLedCmd() {
  int addr = cmdMessenger.readInt16Arg();
  int ledVal = cmdMessenger.readInt16Arg();

  for (int i = 0; i < 20; i++) {
    bool ok = sendIntToPoint(addr, ledVal);
    Log.Info("%d Sending result: %s"CR, i , ok ? "ok" : "fail");
    delay(3000);
  }

}

