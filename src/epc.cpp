#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "b64/cencode.h"
#include "epc.h"

uint8_t EpcHeader(const std::string& epc_hex) {
  return (uint8_t) strtol(epc_hex.substr(0,2).c_str(), NULL, 16);
}

Epc::~Epc() {}

Epc::Epc(const std::string& epc_hex) {
  epc_byte_len_ = epc_hex.size() / 2;
  epc_bytes_ = std::unique_ptr<uint8_t[]>(new uint8_t[epc_byte_len_]);

  // Convert hex byte by byte
  for (std::string::size_type i = 0; i < epc_hex.size(); i += 2) {
    uint8_t b;
    try {
      b = (uint8_t) std::stoul(epc_hex.substr(i, 2), nullptr, 16);
    } catch (const std::invalid_argument& ia) {
      // simply set internal data state to empty state
      epc_byte_len_ = 0;
      epc_bytes_ = std::unique_ptr<uint8_t[]>(new uint8_t[0]);
      return;
    }
    epc_bytes_[i / 2] = b;
  }
}

EpcType Epc::Type() const {
  return UNKNOWN;
}

std::string Epc::Hex() const {
  std::stringstream ss;
  ss << std::hex << std::uppercase;
  for (size_t i = 0; i < epc_byte_len_; ++i) {
    ss << std::setw(2) << std::setfill('0') << (int) epc_bytes_[i];
  }
  return ss.str();
}

std::string Epc::Base64() const {
  // declare a buffer that can hold up to 2^16-1 elements
  // +1 is to simply round up without calling a round function
  // base64 characters needed = 4/3 * (n bytes) rounded up
  int base64_len = 1 + ((4 * epc_byte_len_) / 3);
  char buf[base64_len];

  // c will point to current position in buffer
  char* c = buf;

  // used below to keep track of number of characters added
  int count = 0;

  base64_encodestate s;
  base64_init_encodestate(&s);

  count = base64_encode_block(reinterpret_cast<const char*>(epc_bytes_.get()),
                              epc_byte_len_, c, &s);
  c += count;

  count = base64_encode_blockend(c, &s);
  c += count;

  // null terminate the data
  *c = 0;

  return std::string(buf);
}

std::string Epc::TagUri() const {
  return "";
}

std::string Epc::PureUri() const {
  return "";
}

