
const int maxAllowedWrites = 20;
const int memBase          = 120;

void setupStorage() {
    
  EEPROM.setMemPool(memBase, EEPROMSizeUno);
  EEPROM.setMaxAllowedWrites(maxAllowedWrites);
}
