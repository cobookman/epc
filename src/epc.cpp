#include <stdio.h>
#include <stdlib.h>
#include "epc.h"

uint8_t EpcHeader(const std::string& epc_hex) {
  // header is first byte..so failing fast here
  if (epc_hex.size() < 2) {
    return 0;
  }

  return (uint8_t) strtol(epc_hex.substr(0, 2).c_str(), NULL, 16);
}

Epc::~Epc() {}

Epc::Epc(const std::string& epc_hex) : epc_hex_(epc_hex) {}

EpcType Epc::Type() const {
  return UNKNOWN;
}

std::string Epc::Hex() const {
  return epc_hex_;
}

std::string Epc::Base64() const {
  return "";
}

std::string Epc::TagUri() const {
  return "";
}

std::string Epc::PureUri() const {
  return "";
}
