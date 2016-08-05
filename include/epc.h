#ifndef EPC_H_
#define EPC_H_

#include <string>
#include <stdint.h>
#include <memory>
#include <bitset>

enum EpcType { UNKNOWN, SGTIN96 };

// Gives the epc header of the tag
uint8_t EpcHeader(const std::string& epc_hex);

// Epc base class
class Epc {
 public:
  // Construct epc tag from hex string
  explicit Epc(const std::string& epc_hex);

  // Gives the type of epc tag.
  virtual EpcType Type() const;

  virtual ~Epc();

  // Gives the epc tag's pure gs1 epc uri.
  virtual std::string PureUri() const;

  // Gives the epc tag's tag gs1 epc uri.
  virtual std::string TagUri() const;

  // Gives the epc tag's raw data as a hex string.
  virtual std::string Hex() const;

  // Gives the epc tag's raw data as a base64 string.
  virtual std::string Base64() const;

 protected:
  size_t epc_byte_len_;
  std::unique_ptr<uint8_t[]> epc_bytes_;

};

#endif  // EPC_H_
