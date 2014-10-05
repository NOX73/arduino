void point_initLoop() {
  uint32_t num = pointNum();
  radio_sendEventFrom(num);
  //StreamPack::serialWritePack("hello");
  delay(5000);
}

uint32_t pointNum () {
  return uint32_t(eeprom_point_num);
}


