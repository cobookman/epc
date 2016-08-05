#ifndef SGTIN96_H_
#define SGTIN96_H_

#include "epc.h"

class Sgtin96 : public Epc {
 public:
  virtual ~Sgtin96();

  virtual std::string Uri() const;

  EpcType Type() const;

  std::string Hex() const;

  std::string Base64() const;
};

#endif  // SGTIN96_H_
