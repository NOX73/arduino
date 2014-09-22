#define MAX_ALLOWED_WRITES 20
#define MEM_VABASE 120

void setupStorage() {
  EEPROM.setMemPool(MEM_VABASE, EEPROMSizeUno);
  EEPROM.setMaxAllowedWrites(MAX_ALLOWED_WRITES);

  eeprom_init.restore();

  if (!eeprom_init) {
    eeprom_init = true;
    eeprom_init.save();

    eeprom_point_num = DEFAULT_POINT_NUM;
    eeprom_point_num.save();
  }

}

void clearStorage() {
  for (int i = 0; i < 1024; i++) EEPROM.write(i, 0);
}
