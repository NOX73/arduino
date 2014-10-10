#include <StoragePack.h>

#define MAX_ALLOWED_WRITES 5
#define MEM_VABASE 120

namespace StoragePack {

  EEPROMVar<bool> is_init(false);
  EEPROMVar<uint32_t> point_num(0);

  void setup() {
    EEPROM.setMemPool(MEM_VABASE, EEPROMSizeUno);
    EEPROM.setMaxAllowedWrites(MAX_ALLOWED_WRITES);

    is_init.restore();

    if (!is_init) {
      is_init = true;
      is_init.save();

      point_num = 0;
      point_num.save();
    }

  }

  void clear() {
    for (int i = 0; i < 1024; i++) EEPROM.write(i, 0);
  }

}
