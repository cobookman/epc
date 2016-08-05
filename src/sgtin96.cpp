#include "sgtin96.h"

Sgtin96::~Sgtin96() {}

Sgtin96::Sgtin96(const std::string& epc_hex) : Epc(epc_hex) {}

std::string Sgtin96::PureUri() const {
  // TODO(bookman): Implement method
  return "urn:epc:id:sgtin-96:<filter val>.<company prefix>.<item ref>.<serial>";
}

std::string Sgtin96::TagUri() const {
  // TODO(bookman): Implement method
  return "urn:epc:id:sgtin:<company prefix>.<item ref>.<serial>";
}

EpcType Sgtin96::Type() const {
  return SGTIN96;
}
