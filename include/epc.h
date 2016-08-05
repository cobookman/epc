#ifndef EPC_H_
#define EPC_H_

#include <string>

enum EpcType { UNKNOWN, SGTIN96 };

// Epc base class
class Epc {
 public:
  virtual ~Epc();

  // Gives the epc tag's raw data as the gs1 standard uri.
  virtual std::string Uri() const;

  // Gives the type of epc tag.
  EpcType Type() const;

  // Gives the epc tag's raw data as a hex string.
  std::string Hex() const;

  // Gives the epc tag's raw data as a base64 string.
  std::string Base64() const;

};

// Returns an epc instantiation for the correct tag type
Epc EpcFactory(const std::string& tag);

#endif
