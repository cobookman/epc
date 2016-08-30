#ifndef EPC_H_
#define EPC_H_

#include <string>
#include <stdint.h>
#include <bitset>
#include <vector>

enum EpcType { UNKNOWN, SGTIN96 };

// Gives the epc header of the tag
uint8_t EpcHeader(const std::string& epc_hex);

// Epc base class
class Epc {
 public:
  // Construct epc tag from hex string
  explicit Epc(const std::string& epc_hex);

  virtual ~Epc();

  // Gives the bytes between two positions of epc
  virtual uint64_t Bits(int start, size_t length) const;

  // Sets bits at given position
  virtual bool Set(int start, size_t length, uint64_t data);

  // Gives the type of epc tag.
  virtual EpcType Type() const;

  // Gives the classname of the obj
  virtual std::string ClassName() const;

  // Gives the epc tag's pure gs1 epc uri.
  virtual std::string PureUri() const;

  // Gives the epc tag's tag gs1 epc uri.
  virtual std::string TagUri() const;

  // Gives the epc tag's raw data as a hex string.
  virtual std::string Hex() const;

  // Gives the epc tag's raw data as a base64 string.
  virtual std::string Base64() const;

 protected:
  std::vector<bool> epc_bits_;

};

#endif  // EPC_H_
