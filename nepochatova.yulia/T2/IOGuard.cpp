#include "IOGuard.h"
#include <algorithm>
#include <cctype>
#include <string>

namespace nepochatova {

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    in >> dest.last_;
    if (in && (std::tolower(static_cast<unsigned char>(dest.last_)) !=
               std::tolower(static_cast<unsigned char>(dest.expected_)))) {
      in.setstate(std::ios_base::failbit);
               }
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    std::string data;
    in >> data;
    if (in && data != dest.expected_) {
      in.setstate(std::ios_base::failbit);
    }
    return in;
  }

  IOguard::IOguard(std::basic_ios<char>& s):
    s_(s),
    precision_(s.precision()),
    width_(s.width()),
    fmt_(s.flags()),
    fill_(s.fill())
  {}

  IOguard::~IOguard() {
    s_.precision(precision_);
    s_.width(width_);
    s_.flags(fmt_);
    s_.fill(fill_);
  }
}