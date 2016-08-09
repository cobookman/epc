#include "gtin.h"
#include "encodings/sgtin.h"

Sgtin::Sgtin(const std::string& epc_hex) : Epc(epc_hex) {}

std::string Sgtin::Gtin14() const {
  // TODO(bookman): Implement this method
  std::string company_prefix = "1234";
  std::string item_ref = "568821111";
  Gtin gtin(company_prefix, item_ref);
  return gtin.Gtin14();
}

std::string Sgtin::CompanyPrefix() const {
  // TODO(bookman): Implement this method
  return "";
}

std::string Sgtin::ItemRef() const {
  // TODO(bookman): Implement this method
  return "";
}

Sgtin::FilterType Sgtin::Filter() const {
  // TODO(bookman): Implement this method
  return Sgtin::ALL_OTHERS;
}

Sgtin96::~Sgtin96() {}

Sgtin96::Sgtin96(const std::string& epc_hex) : Sgtin(epc_hex) {}

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

std::string Sgtin96::ClassName() const {
  return "Sgtin96";
}

long Sgtin96::Serial() const {
  // TODO(bookman): Implement this method
  return -1;
}

