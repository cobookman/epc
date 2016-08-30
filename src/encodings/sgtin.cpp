#include "gtin.h"
#include "encodings/sgtin.h"
#include <iostream>

Sgtin::Sgtin(const std::string& epc_hex) : Epc(epc_hex) {}

std::string Sgtin::Gtin14() const {
  // TODO(bookman): Implement this method
  std::string company_prefix = CompanyPrefix();
  std::string item_ref = ItemRef();
  std::string indicator = Indicator();

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

Sgtin96::Sgtin96(uint8_t filter_value, uint64_t company_prefix, uint8_t company_prefix_length, uint32_t item_ref, uint64_t serial) : Sgtin("") {
  uint8_t partition_value = 12 - company_prefix_length;
  uint8_t company_prefix_bits = 0;
  switch (partition_value) {
    case 0:
      company_prefix_bits = 40;
      break;
    case 1:
      company_prefix_bits = 37;
      break;
    case 2:
      company_prefix_bits = 34;
      break;
    case 3:
      company_prefix_bits = 30;
      break;
    case 4:
      company_prefix_bits = 27;
      break;
    case 5:
      company_prefix_bits = 24;
      break;
    case 6:
      company_prefix_bits = 20;
      break;
  }

  // Error invalid company prefix length
  if (company_prefix_bits == 0) {
    return;
  }

  uint8_t item_ref_bits =  44 - company_prefix_bits;
  uint8_t sgtin96_header = 0x30;
  bool status = true;
  std::cout << "Setting header" << std::endl;
  status &= Set(0, 8, sgtin96_header);
  std::cout << "Setting filter: " <<(int) filter_value << "END" << std::endl;
  status &= Set(8, 3, filter_value);
  std::cout << "Setting partition" << std::endl;
  status &= Set(11, 3, partition_value);
  std::cout << "Setting comp prefix " << company_prefix << "bits: " << company_prefix_bits << std::endl;
  status &= Set(14, company_prefix_bits, company_prefix);
  std::cout << "Set item ref" << std::endl;
  status &= Set(14 + company_prefix_bits, item_ref_bits, item_ref);
  std::cout << "Set serial" << std::endl;
  status &= Set(58, 38, serial);
  std::cout << "YAY" << std::endl;

  // Error going to null state
  if (!status) {
    epc_bits_.clear();
  }
}

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

Sgtin96Builder* Sgtin96::Build(void) {
  return new Sgtin96Builder();
}


Sgtin96Builder::Sgtin96Builder() :
  item_ref_(0), company_prefix_(0), company_prefix_length_(0), serial_(0), filter_(0) {
}

Sgtin96Builder* Sgtin96Builder::ItemRef(const std::string& item_ref) {
  return ItemRef(std::stoi(item_ref));
}

Sgtin96Builder* Sgtin96Builder::ItemRef(const uint32_t item_ref) {
  item_ref_ = item_ref;
  return this;
}

Sgtin96Builder* Sgtin96Builder::CompanyPrefix(const std::string& company_prefix) {
  return CompanyPrefix(std::stoull(company_prefix), company_prefix.length());
}

Sgtin96Builder* Sgtin96Builder::CompanyPrefix(const uint64_t company_prefix, uint8_t company_prefix_length) {
  company_prefix_ = company_prefix;
  company_prefix_length_ = company_prefix_length;
  return this;
}

Sgtin96Builder* Sgtin96Builder::Serial(const std::string& serial) {
  return Serial(std::stoull(serial));
}

Sgtin96Builder* Sgtin96Builder::Serial(const uint64_t serial) {
  serial_ = serial;
  return this;
}

Sgtin96Builder* Sgtin96Builder::Filter(const uint8_t filter) {
  filter_ = filter;
  return this;
}

Sgtin96Builder* Sgtin96Builder::Gtin(const std::string& gtin, const uint8_t company_prefix_length) {
  // TODO(bookman): Refactor this to create a digit array & re-use code.
  return Gtin(std::stoull(gtin), company_prefix_length);
}

Sgtin96Builder* Sgtin96Builder::Gtin(uint64_t gtin, const uint8_t company_prefix_length) {
  company_prefix_length_ = company_prefix_length;

  uint8_t gtin14[14];  // default value of uint8_t is `0`

  // convert gtin to gtin14 by padding with 0, and allowing easy number
  // lookups.
  for (int i = 13; i >= 0; i--) {
    gtin14[i] = gtin % 10;
    gtin /= 10;
  }

  // filter is 1st digit
  filter_ = gtin14[0];

  // set company prefix to gtin14[1:company_prefix_length+1];
  company_prefix_ = 0;
  for (int i = 1; i < 1 + company_prefix_length_; ++i) {
    company_prefix_ *= 10;
    company_prefix_ += gtin14[i];
  }

  // set item_ref to gtin14[1+company_prefix_length:13]
  item_ref_ = 0;
  for (int i = 1 + company_prefix_length_; i < 13; ++i) {
    item_ref_ *= 10;
    item_ref_ += gtin14[i];
  }

  return this;
}

Sgtin96 Sgtin96Builder::Build(void) {
  auto tag = Sgtin96(filter_, company_prefix_, company_prefix_length_, item_ref_, serial_);
  delete this;
  return tag;
}
