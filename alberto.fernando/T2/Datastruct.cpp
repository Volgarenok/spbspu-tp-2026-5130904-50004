#include "Datastruct.hpp"

#include <cctype>
#include <cmath>
#include <iomanip>
#include <istream>
#include <ostream>
#include <string>
#include <utility>

#include "io_utils.hpp"

namespace alberto {
namespace detail {
bool readToken(std::istream& in, std::string& token)
{
  token.clear();
  char c = '\0';
  while (in.get(c)) {
    if (c == ':' || c == ')') {
      in.putback(c);
      break;
    }
    token += c;
  }
  return !token.empty();
}

bool parseSignedLongLit(const std::string& token, long long& value)
{
  if (token.size() < 3) {
    return false;
  }
  const size_t sz = token.size();
  const char   l1 = static_cast< char >(std::tolower(
      static_cast< unsigned char >(token[sz - 2])));
  const char   l2 = static_cast< char >(std::tolower(
      static_cast< unsigned char >(token[sz - 1])));
  if (l1 != 'l' || l2 != 'l') {
    return false;
  }
  const std::string digits = token.substr(0, sz - 2);
  if (digits.empty()) {
    return false;
  }
  const size_t start = (digits[0] == '-') ? 1 : 0;
  if (start == digits.size()) {
    return false;
  }
  for (size_t i = start; i < digits.size(); ++i) {
    if (!std::isdigit(static_cast< unsigned char >(digits[i]))) {
      return false;
    }
  }
  try {
    value = std::stoll(digits);
  } catch (...) {
    return false;
  }
  return true;
}

bool readRational(std::istream& in,
                  std::pair< long long, unsigned long long >& value)
{
  in >> alberto::ExpectChar{'('};
  if (!in) {
    return false;
  }

  long long          numerator   = 0;
  unsigned long long denominator = 0;
  bool               gotN        = false;
  bool               gotD        = false;

  for (int i = 0; i < 2; ++i) {
    in >> alberto::ExpectChar{':'};
    if (!in) {
      return false;
    }

    std::string fieldName;
    char        c = '\0';
    while (in.get(c) && c != ' ') {
      fieldName += c;
    }
    if (!in) {
      return false;
    }

    std::string tok;
    if (!readToken(in, tok)) {
      return false;
    }

    if (fieldName == "N") {
      try {
        numerator = std::stoll(tok);
        gotN      = true;
      } catch (...) {
        return false;
      }
    } else if (fieldName == "D") {
      try {
        denominator = std::stoull(tok);
        gotD        = true;
      } catch (...) {
        return false;
      }
    } else {
      return false;
    }
  }
  in >> alberto::ExpectChar{':'} >> alberto::ExpectChar{')'};
  if (!in || !gotN || !gotD) {
    return false;
  }

  value = {numerator, denominator};
  return true;
}

bool readField(std::istream& in,
               const std::string& name,
               long long& key1,
               std::pair< long long, unsigned long long >& key2,
               std::string& key3,
               bool& ok1,
               bool& ok2,
               bool& ok3)
{
  if (name == "key1") {
    if (ok1) {
      return false;
    }
    std::string tok;
    if (!readToken(in, tok)) {
      return false;
    }
    if (!parseSignedLongLit(tok, key1)) {
      return false;
    }
    ok1 = true;

  } else if (name == "key2") {
    if (ok2) {
      return false;
    }
    if (!readRational(in, key2)) {
      return false;
    }
    ok2 = true;

  } else if (name == "key3") {
    if (ok3) {
      return false;
    }
    if (!(in >> std::quoted(key3))) {
      return false;
    }
    ok3 = true;

  } else {
    return false;
  }
  return true;
}

}
}

std::istream&
alberto::operator>>(std::istream& in, DataStruct& ds)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  DataStruct tmp{};
  bool       ok1 = false;
  bool       ok2 = false;
  bool       ok3 = false;

  in >> alberto::ExpectChar{'('} >> alberto::ExpectChar{':'};
  if (!in) {
    return in;
  }

  for (int i = 0; i < 3; ++i) {
    std::string name;
    char        c = '\0';
    while (in.get(c) && c != ' ') {
      name += c;
    }
    if (!in) {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (!detail::readField(in, name, tmp.key1, tmp.key2, tmp.key3, ok1, ok2, ok3)) {
      in.setstate(std::ios::failbit);
      return in;
    }

    in >> alberto::ExpectChar{':'};
    if (!in) {
      return in;
    }
  }

  in >> alberto::ExpectChar{')'};
  if (!in) {
    return in;
  }

  if (!ok1 || !ok2 || !ok3) {
    in.setstate(std::ios::failbit);
    return in;
  }

  ds = std::move(tmp);
  return in;
}

std::ostream&
alberto::operator<<(std::ostream& out, const DataStruct& ds)
{
  out << "(:key1 " << ds.key1 << "ll"
      << ":key2 (:N " << ds.key2.first
      << ":D " << ds.key2.second << ":)"
      << ":key3 " << std::quoted(ds.key3) << ":)";
  return out;
}

bool
alberto::operator<(const DataStruct& a, const DataStruct& b)
{
  if (a.key1 != b.key1) {
    return a.key1 < b.key1;
  }
  static constexpr double EPSILON = 1e-15;

  const double ra = (a.key2.second != 0)
      ? static_cast< double >(a.key2.first)
        / static_cast< double >(a.key2.second)
      : static_cast< double >(a.key2.first);
  const double rb = (b.key2.second != 0)
      ? static_cast< double >(b.key2.first)
        / static_cast< double >(b.key2.second)
      : static_cast< double >(b.key2.first);

  if (std::abs(ra - rb) > EPSILON) {
    return ra < rb;
  }

  return a.key3.size() < b.key3.size();
}
