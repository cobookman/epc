#ifndef ENCODINGS_SGTIN96_H_
#define ENCODINGS_SGTIN96_H_

#include <epc.h>

class Sgtin : public Epc {
 public:
  enum FilterType {
    ALL_OTHERS = 0,
    POS = 1,
    FULL_CASE = 2,
    RESERVED = 3,
    INNER_PACK = 4,
    UNIT_LOAD = 6,
    COMPONENT_INSIDE_PRODUCT = 7,
  };

  explicit Sgtin(const std::string& epc_hex);

  virtual EpcType Type() const = 0;

  virtual std::string ClassName() const = 0;

  virtual std::string PureUri() const = 0;

  virtual std::string TagUri() const = 0;

  virtual std::string Gtin14() const;

  virtual std::string CompanyPrefix() const;

  virtual std::string ItemRef() const;

  virtual FilterType Filter() const;
};

class Sgtin96 : public Sgtin {
 public:
  explicit Sgtin96(const std::string& epc_hex);

  virtual ~Sgtin96();

  virtual EpcType Type() const override;

  virtual std::string ClassName() const override;

  virtual std::string PureUri() const override;

  virtual std::string TagUri() const override;

  // virtual std::string CompanyPrefix() const;

  // virtual std::string ItemRef() const;

  // virtual FilterType Filter() const;

  virtual long Serial() const;

};


#endif  // ENCODINGS_SGTIN96_H_
