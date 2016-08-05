#include "factory.h"
#include "sgtin96.h"

Epc EpcFactory(const std::string& tag) {
  // TODO(bookman): Implement this method
  return Sgtin96();
}

