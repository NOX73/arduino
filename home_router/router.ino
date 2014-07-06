void setupRouter() {
}

void routerLoop() {
  cmdMessenger.feedinSerialData();
  char val[] = {"0;"};
  sendStrToPoint(1, val, sizeof(val));
  delay(3000);
}
