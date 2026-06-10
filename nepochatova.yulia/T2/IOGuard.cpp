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

  std::istream& operator>>(std::istream& in, SllLitIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    long long value = 0;
    char c1 = 0, c2 = 0;
    in >> value >> DelimiterIO{'l', c1} >> DelimiterIO{'l', c2};
    std::string lit{c1, c2};
    std::transform(lit.begin(), lit.end(), lit.begin(), ::tolower);
    if (in && lit == "ll") {
      dest.ref_ = value;
    } else {
      in.setstate(std::ios_base::failbit);
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const SllLitIO& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    out << src.ref_ << "ll";
    return out;
  }

  std::istream& operator>>(std::istream& in, UllLitIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    unsigned long long value = 0;
    char c1 = 0, c2 = 0, c3 = 0;
    in >> value >> DelimiterIO{'u', c1} >> DelimiterIO{'l', c2} >> DelimiterIO{'l', c3};
    std::string lit{c1, c2, c3};
    std::transform(lit.begin(), lit.end(), lit.begin(), ::tolower);
    if (in && lit == "ull") {
      dest.ref_ = value;
    } else {
      in.setstate(std::ios_base::failbit);
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const UllLitIO& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) return out;
    out << src.ref_ << "ull";
    return out;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char last = 0;
    in >> DelimiterIO{'"', last};
    if (!in) return in;
    std::getline(in, dest.ref_, '"');
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