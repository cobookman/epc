#ifndef SGTIN96_H_
#define SGTIN96_H_

#include "epc.h"

class Sgtin96 : public Epc {
 public:
  explicit Sgtin96(const std::string& epc_hex);

  virtual ~Sgtin96();

  virtual EpcType Type() const;

  virtual std::string PureUri() const;

  virtual std::string TagUri() const;

};

#endif  // SGTIN96_H_
