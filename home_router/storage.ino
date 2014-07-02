
#define MAX_ALLOWED_WRITES 20
#define MEM_VABASE 120

void setupStorage() {
  EEPROM.setMemPool(MEM_VABASE, EEPROMSizeUno);
  EEPROM.setMaxAllowedWrites(MAX_ALLOWED_WRITES);

  led_val.restore();
  radio_num.restore();
}
