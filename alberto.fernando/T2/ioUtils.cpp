#include "io_utils.hpp"

#include <cctype>
#include <istream>
#include <string>
std::istream&
alberto::operator>>(std::istream& in, ExpectChar ec)
{
  char c = '\0';
  if (in >> c && c != ec.expected_) {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream&
alberto::operator>>(std::istream& in, ExpectStr es)
{
  const std::string expected(es.expected_);
  for (char ch : expected) {
    char c = '\0';
    if (!(in >> std::noskipws >> c) || c != ch) {
      in.setstate(std::ios::failbit);
      break;
    }
  }
  in >> std::skipws;
  return in;
}
