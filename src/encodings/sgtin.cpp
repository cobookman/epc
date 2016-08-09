#include "gtin.h"
#include "encodings/sgtin.h"
#include <iostream>

Sgtin::Sgtin(const std::string& epc_hex) : Epc(epc_hex) {}

std::string Sgtin::Gtin14() const {
  // TODO(bookman): Implement this method
  std::string company_prefix = CompanyPrefix();
  std::string item_ref = ItemRef();
  std::string indicator = Indicator();

  std::cout << "Company prefix: " << company_prefix << std::endl;
  Gtin gtin(indicator, company_prefix, item_ref);
  return gtin.Gtin14();
}

std::string Sgtin::CompanyPrefix() const {
  int partition = Partition();

  std::string::size_type digits = 0;
  int bits = 0;
  switch (partition) {
    case 0:
      bits = 40;
      digits = 12;
      break;
    case 1:
      bits = 37;
      digits = 11;
      break;
    case 2:
      bits = 34;
      digits = 10;
      break;
    case 3:
      bits = 30;
      digits = 9;
      break;
    case 4:
      bits = 27;
      digits = 8;
      break;
    case 5:
      bits = 24;
      digits = 7;
      break;
    case 6:
      bits = 20;
      digits = 6;
      break;
  }

  std::string value = std::to_string(Bits(14, bits));

  while (value.length() < digits) {
    value = "0" + value;
  }

  return value;
}

std::string Sgtin::ItemRefAndPad() const {
  int partition = Partition();

  std::string::size_type digits = 0;
  int start_bit = 0;
  int bits = 0;
  switch (partition) {
    case 0:
      start_bit = 14 + 40;
      bits = 4;
      digits = 1;
      break;
    case 1:
      start_bit = 14 + 37;
      bits = 7;
      digits = 2;
      break;
    case 2:
      start_bit = 14 + 34;
      bits = 10;
      digits = 3;
      break;
    case 3:
      start_bit = 14 + 30;
      bits = 14;
      digits = 4;
      break;
    case 4:
      start_bit = 14 + 27;
      bits = 17;
      digits = 5;
      break;
    case 5:
      start_bit = 14 + 24;
      bits = 20;
      digits = 6;
      break;
    case 6:
      start_bit = 14 + 20;
      bits = 24;
      digits = 7;
      break;
  }

  std::string value = std::to_string(Bits(start_bit, bits));

  while (value.length() < digits) {
    value = "0" + value;
  }

  return value;
}

std::string Sgtin::ItemRef() const {
  return ItemRefAndPad().substr(1);
}

std::string Sgtin::Indicator() const {
  return ItemRefAndPad().substr(0, 1);
}


Sgtin::FilterType Sgtin::Filter() const {
  int value = Bits(8, 3);
  FilterType f = RESERVED;
  switch (value) {
    case 0:
      f = ALL_OTHERS;
      break;
    case 1:
      f = POS;
      break;
    case 2:
      f = FULL_CASE;
      break;
    case 3:
      f = RESERVED;
      break;
    case 4:
      f = INNER_PACK;
      break;
    case 5:
      f = RESERVED;
      break;
    case 6:
      f = UNIT_LOAD;
      break;
    case 7:
      f = COMPONENT_INSIDE_PRODUCT;
      break;
  }
  return f;
}

int Sgtin::Partition() const {
  return Bits(8 + 3, 3);
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
  return Bits(96-38, 38);
}

