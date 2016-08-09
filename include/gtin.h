#ifndef GTIN_H_
#define GTIN_H_

#include <string>

class Gtin {
 public:
  Gtin(const std::string& indicator, const std::string& company_prefix, const std::string& item_ref);
  std::string Gtin14() const;
  std::string Gtin12() const;

  // Calculates the check digit of a gtin. If a non numeric (0-9) string
  // passed, then an empty string returned.
  static std::string CheckDigit(const std::string& minus_check_digit);

 private:
  std::string indicator_;
  std::string company_prefix_;
  std::string item_ref_;
  std::string check_digit_;
};

#endif  // GTIN_H_
