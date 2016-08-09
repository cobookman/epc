#include "gtin.h"

Gtin::Gtin(const std::string& company_prefix, const std::string& item_ref)
  : company_prefix_(company_prefix), item_ref_(item_ref) {
    check_digit_ = CheckDigit(company_prefix_ + item_ref_);
}

std::string Gtin::Gtin14() const {
  std::string out = company_prefix_ + item_ref_;
  out += CheckDigit(out);
  while (out.size() < 14) {
    out = "0" + out;
  }
  return out;
}

std::string Gtin::Gtin12() const {
  return Gtin14().substr(2, 12);
}

std::string Gtin::CheckDigit(const std::string& minus_check_digit) {
  int digit_sum = 0;
  for (std::string::size_type i = 0; i < minus_check_digit.size(); ++i) {
    const int digit = minus_check_digit[i] - '0';
    if (digit < 0 || digit > 9) {
      return "";
    }
    digit_sum += (3 - (i % 2) * 2) * digit;
  }

  const char check_digit = '0' + ((10 - (digit_sum % 10)) % 10);
  return std::string(1, check_digit);
}

