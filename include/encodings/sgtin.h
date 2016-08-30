#ifndef ENCODINGS_SGTIN96_H_
#define ENCODINGS_SGTIN96_H_

#include <epc.h>
class Sgtin96Builder;

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

  virtual std::string Indicator() const;

  virtual FilterType Filter() const;

  virtual int Partition() const;

 private:
  // contains the item ref & pad digit see gs1 specs as to why
  virtual std::string ItemRefAndPad() const;
};

class Sgtin96 : public Sgtin {
 public:
  explicit Sgtin96(const std::string& epc_hex);

  Sgtin96(uint8_t filter_value, uint64_t company_prefix, uint8_t company_prefix_length, uint32_t item_ref, uint64_t serial);

  virtual ~Sgtin96();

  virtual EpcType Type() const override;

  virtual std::string ClassName() const override;

  virtual std::string PureUri() const override;

  virtual std::string TagUri() const override;

  virtual long Serial() const;

  static Sgtin96Builder* Build(void);
};


// From http://www.swig.org/Doc2.0/SWIGPlus.html#SWIGPlus_nn18
// Don't return references to objects allocated as local variables on the stack. SWIG doesn't make a copy of the objects so this will probably cause your program to crash.
// Hence the return by pointer vs return ref, and the builder declared on heap.
// Do recognize that the builder will self destruct itself though, and is a
// `smart` pointer
class Sgtin96Builder {
 public:
  Sgtin96Builder();

  // ItemRef can be at most 7 positive base10 digits (4-24 bits). fitting in an
  // int
  Sgtin96Builder* ItemRef(const std::string& item_ref);
  Sgtin96Builder* ItemRef(const uint32_t item_ref);

  // ComapnyPrefix can be at most 12 positive base10 digits (20-40 bits)
  Sgtin96Builder* CompanyPrefix(const std::string& company_prefix);
  Sgtin96Builder* CompanyPrefix(const uint64_t company_prefix, const uint8_t company_prefix_length);

  // Serial is 38 bits long
  Sgtin96Builder* Serial(const std::string& serial);
  Sgtin96Builder* Serial(const uint64_t serial);

  // Filter Value is 3 bits
  Sgtin96Builder* Filter(const uint8_t filter);

  // Parses company prefix, item ref, and filter from gtin14
  Sgtin96Builder* Gtin(const std::string& gtin, const uint8_t company_prefix_length);
  Sgtin96Builder* Gtin(const uint64_t gtin, const uint8_t company_prefix_length);

  // Builds the EpcSgtin96 and cleans itself off the heap `delete this`.
  Sgtin96 Build(void);

 private:
  uint32_t item_ref_;
  uint64_t company_prefix_;
  uint8_t company_prefix_length_;
  uint64_t serial_;
  uint8_t filter_;
};

#endif  // ENCODINGS_SGTIN96_H_
