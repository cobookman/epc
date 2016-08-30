#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <assert.h>

#include "b64/cencode.h"
#include "epc.h"

uint8_t EpcHeader(const std::string& epc_hex) {
  return (uint8_t) strtol(epc_hex.substr(0,2).c_str(), NULL, 16);
}

Epc::~Epc() {}

Epc::Epc(const std::string& epc_hex) {
  std::vector<bool> bits;

  // Convert hex byte by byte
  for (std::string::size_type i = 0; i < epc_hex.size(); i += 2) {
    int b;
    try {
      b = std::stoul(epc_hex.substr(i, 2), nullptr, 16);
    } catch (const std::exception& e) {
      // Not a good hex str
      return;
    }

    for (int i = 7; i > -1; --i) {
      bool bit = (b >> i) & 0x1;
      bits.push_back(bit);
    }
  }

  epc_bits_ = bits;
}

EpcType Epc::Type() const {
  return UNKNOWN;
}

std::string Epc::ClassName() const {
  return "Epc";
}

uint64_t Epc::Bits(int start, size_t length) const {
  // check we don't overflow uint64_t
  assert(length <= 64);

  // check we index out of bounds epc_bits_ vector
  assert(epc_bits_.size() >= (uint64_t) (start + length));

  uint64_t out = 0;
  for (size_t i = start; i < (size_t) start + length; ++i) {
    out <<= 1;
    out |= epc_bits_[i] & 0x1;
  }
  return out;
}

bool Epc::Set(int start, size_t length, uint64_t data) {
  // Requesting us to overflow.
  if (length > 64) {
    return false;
  }

  int end_i = start + length - 1;
  // extend vector size to our start postion if necessary
  while ((size_t) end_i >= epc_bits_.size()) {
    epc_bits_.push_back(0);
  }

  // fil data in from least to biggest digit
  for (int i = end_i; i >= start; --i) {
    // grab smallest bit & append
    bool bit = (bool) (data & 0x1);
    epc_bits_[i] = bit;
    // start lookingat next bit
    data >>= 1;
  }

  std::cout << "Bits: ";
  for (auto b : epc_bits_) {
    std::cout << (int) b;
   }
  std::cout << std::endl;
  return true;
}

std::string Epc::Hex() const {
  std::stringstream ss;
  ss << std::hex << std::uppercase;
  for (size_t i = 0; i < epc_bits_.size(); i += 8) {
    int b = Bits(i, 8);
    ss << std::setw(2) << std::setfill('0') << b;
  }

  return ss.str();
}

std::string Epc::Base64() const {
  const int num_epc_bytes = epc_bits_.size() / 8;

  // declare a buffer that can hold up to 2^16-1 elements
  // +1 is to simply round up without calling a round function
  // base64 characters needed = 4/3 * (n bytes) rounded up
  int base64_len = 1 + ((4 * num_epc_bytes) / 3);
  char buf[base64_len];

  // c will point to current position in buffer
  char* c = buf;

  // used below to keep track of number of characters added
  int count = 0;

  base64_encodestate s;
  base64_init_encodestate(&s);

  char epc_bytes[num_epc_bytes];
  for (size_t i = 0; i < epc_bits_.size(); i += 8) {
    char b = (char) Bits(i, 8);
    epc_bytes[i / 8] = b;
  }

  count = base64_encode_block(epc_bytes, num_epc_bytes, c, &s);
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

