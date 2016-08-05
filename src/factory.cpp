#include <stdint.h>
#include <iostream>
#include "factory.h"
#include "sgtin96.h"

Epc* EpcFactory(const std::string& epc_hex) {
  // TODO(bookman): Implement this method
  uint8_t header = EpcHeader(epc_hex);
  switch (header) {
    case 0x30:
      std::cout << "SGTIN96" << std::endl;
      return new Sgtin96(epc_hex);
    default:
      return new Epc(epc_hex);
  }
}

