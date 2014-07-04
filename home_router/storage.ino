
#define MAX_ALLOWED_WRITES 20
#define MEM_VABASE 120

void setupStorage() {
  EEPROM.setMemPool(MEM_VABASE, EEPROMSizeUno);
  EEPROM.setMaxAllowedWrites(MAX_ALLOWED_WRITES);

  eeprom_init.restore();

  if (!eeprom_init) {
    Log.Info("Init eeprom with default values."CR);
    
    led_val = HIGH;
    led_val.save();

    radio_num = RADIO_NUM;
    radio_num.save();

    eeprom_init = true;
    eeprom_init.save();
  }


}
