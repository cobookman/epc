#include <stdio.h>
#include "epc.h"

Epc::~Epc() {}

EpcType Epc::Type() const {
  // TODO(bookman): Implement this method
  return UNKNOWN;
}

std::string Epc::Hex() const {
  // TODO(bookman): Implement this method
  return "FF";
}

std::string Epc::Base64() const {
  // TODO(bookman): Implement this method
  return "";
}

std::string Epc::Uri() const {
  // TODO(bookman): Return a unknown tag uri
  return "";
}

