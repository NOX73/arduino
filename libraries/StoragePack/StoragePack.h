#ifndef StoragePack_h
#define StoragePack_h

#include <EEPROMVar.h>
#include <EEPROMex.h>

namespace StoragePack {

  extern EEPROMVar<bool> is_init;
  extern EEPROMVar<uint32_t> point_num;

  void setup();
  void clear();

}


#endif
