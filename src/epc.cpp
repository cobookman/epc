#include <stdio.h>
#include <stdlib.h>
#include "b64/cencode.h"
#include "epc.h"

uint8_t EpcHeader(const std::string& epc_hex) {
  return (uint8_t) strtol(epc_hex.substr(0,2).c_str(), NULL, 16);
}

Epc::~Epc() {}

Epc::Epc(const std::string& epc_hex) : epc_hex_(epc_hex) {
  epc_bytes_len_ = epc_hex_.size() / 2;
  uint8_t* buf = new uint8_t[epc_bytes_len_];
  for (size_t i = 0; i < epc_bytes_len_; i += 2) {
    std::string byte_str = epc_hex_.substr(i, 2);
    buf[i%2] = (uint8_t) strtol(byte_str.c_str(), NULL, 16);
  }

  epc_bytes_ = std::unique_ptr<uint8_t[]>(buf);
}

EpcType Epc::Type() const {
  return UNKNOWN;
}

std::string Epc::Hex() const {
  return epc_hex_;
}

std::string Epc::Base64() const {
  // declare a buffer that can hold up to 2^16-1 elements
  char buf[65535];

  // c will point to current position in buffer
  char* c = buf;

  // used below to keep track of number of characters added
  int count = 0;

  base64_encodestate s;
  base64_init_encodestate(&s);

  count = base64_encode_block(reinterpret_cast<const char*>(epc_bytes_.get()),
                              epc_bytes_len_, c, &s);
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

